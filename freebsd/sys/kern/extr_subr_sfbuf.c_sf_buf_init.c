#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct sf_buf {scalar_t__ kva; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int NSFBUFS ; 
 int PAGE_SIZE ; 
 scalar_t__ PMAP_HAS_DMAP ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct sf_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int /*<<< orphan*/  free_entry ; 
 int /*<<< orphan*/  hashinit (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ kva_alloc (int) ; 
 struct sf_buf* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nsfbufs ; 
 int /*<<< orphan*/  sf_buf_active ; 
 scalar_t__ sf_buf_alloc_want ; 
 int /*<<< orphan*/  sf_buf_freelist ; 
 int /*<<< orphan*/  sf_buf_hashmask ; 
 int /*<<< orphan*/  sf_buf_lock ; 

__attribute__((used)) static void
sf_buf_init(void *arg)
{
	struct sf_buf *sf_bufs;
	vm_offset_t sf_base;
	int i;

	if (PMAP_HAS_DMAP)
		return;

	nsfbufs = NSFBUFS;
	TUNABLE_INT_FETCH("kern.ipc.nsfbufs", &nsfbufs);

	sf_buf_active = hashinit(nsfbufs, M_TEMP, &sf_buf_hashmask);
	TAILQ_INIT(&sf_buf_freelist);
	sf_base = kva_alloc(nsfbufs * PAGE_SIZE);
	sf_bufs = malloc(nsfbufs * sizeof(struct sf_buf), M_TEMP,
	    M_WAITOK | M_ZERO);
	for (i = 0; i < nsfbufs; i++) {
		sf_bufs[i].kva = sf_base + i * PAGE_SIZE;
		TAILQ_INSERT_TAIL(&sf_buf_freelist, &sf_bufs[i], free_entry);
	}
	sf_buf_alloc_want = 0;
	mtx_init(&sf_buf_lock, "sf_buf", NULL, MTX_DEF);
}