#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
struct zbuf {int zb_uaddr; size_t zb_size; size_t zb_numpages; struct bpf_zbuf_header* zb_header; int /*<<< orphan*/ ** zb_pages; } ;
struct vm_map {int dummy; } ;
struct thread {TYPE_2__* td_proc; } ;
struct sf_buf {int dummy; } ;
struct bpf_zbuf_header {int dummy; } ;
struct TYPE_4__ {TYPE_1__* p_vmspace; } ;
struct TYPE_3__ {struct vm_map vm_map; } ;

/* Variables and functions */
 size_t BPF_MAX_PAGES ; 
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  M_BPF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PAGE_MASK ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  bzero (struct bpf_zbuf_header*,int) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sf_buf_kva (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zbuf_free (struct zbuf*) ; 
 int /*<<< orphan*/ * zbuf_sfbuf_get (struct vm_map*,int) ; 

__attribute__((used)) static int
zbuf_setup(struct thread *td, vm_offset_t uaddr, size_t len,
    struct zbuf **zbp)
{
	struct zbuf *zb;
	struct vm_map *map;
	int error, i;

	*zbp = NULL;

	/*
	 * User address must be page-aligned.
	 */
	if (uaddr & PAGE_MASK)
		return (EINVAL);

	/*
	 * Length must be an integer number of full pages.
	 */
	if (len & PAGE_MASK)
		return (EINVAL);

	/*
	 * Length must not exceed per-buffer resource limit.
	 */
	if ((len / PAGE_SIZE) > BPF_MAX_PAGES)
		return (EINVAL);

	/*
	 * Allocate the buffer and set up each page with is own sf_buf.
	 */
	error = 0;
	zb = malloc(sizeof(*zb), M_BPF, M_ZERO | M_WAITOK);
	zb->zb_uaddr = uaddr;
	zb->zb_size = len;
	zb->zb_numpages = len / PAGE_SIZE;
	zb->zb_pages = malloc(sizeof(struct sf_buf *) *
	    zb->zb_numpages, M_BPF, M_ZERO | M_WAITOK);
	map = &td->td_proc->p_vmspace->vm_map;
	for (i = 0; i < zb->zb_numpages; i++) {
		zb->zb_pages[i] = zbuf_sfbuf_get(map,
		    uaddr + (i * PAGE_SIZE));
		if (zb->zb_pages[i] == NULL) {
			error = EFAULT;
			goto error;
		}
	}
	zb->zb_header =
	    (struct bpf_zbuf_header *)sf_buf_kva(zb->zb_pages[0]);
	bzero(zb->zb_header, sizeof(*zb->zb_header));
	*zbp = zb;
	return (0);

error:
	zbuf_free(zb);
	return (error);
}