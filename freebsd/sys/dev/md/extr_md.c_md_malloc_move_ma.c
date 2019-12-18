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
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  int /*<<< orphan*/  u_char ;
struct sf_buf {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int EDOOFUS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
#define  MD_MALLOC_MOVE_CMP 132 
#define  MD_MALLOC_MOVE_FILL 131 
#define  MD_MALLOC_MOVE_READ 130 
#define  MD_MALLOC_MOVE_WRITE 129 
#define  MD_MALLOC_MOVE_ZERO 128 
 int PAGE_SIZE ; 
 int SFB_CPUPRIVATE ; 
 int SFB_NOWAIT ; 
 int /*<<< orphan*/  bcopy (char*,void*,int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  cpu_flush_dcache (char*,int) ; 
 int imin (int,unsigned int) ; 
 scalar_t__ md_malloc_wait ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sched_pin () ; 
 int /*<<< orphan*/  sched_unpin () ; 
 struct sf_buf* sf_buf_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sf_buf_free (struct sf_buf*) ; 
 scalar_t__ sf_buf_kva (struct sf_buf*) ; 

__attribute__((used)) static int
md_malloc_move_ma(vm_page_t **mp, int *ma_offs, unsigned sectorsize,
    void *ptr, u_char fill, int op)
{
	struct sf_buf *sf;
	vm_page_t m, *mp1;
	char *p, first;
	off_t *uc;
	unsigned n;
	int error, i, ma_offs1, sz, first_read;

	m = NULL;
	error = 0;
	sf = NULL;
	/* if (op == MD_MALLOC_MOVE_CMP) { gcc */
		first = 0;
		first_read = 0;
		uc = ptr;
		mp1 = *mp;
		ma_offs1 = *ma_offs;
	/* } */
	sched_pin();
	for (n = sectorsize; n != 0; n -= sz) {
		sz = imin(PAGE_SIZE - *ma_offs, n);
		if (m != **mp) {
			if (sf != NULL)
				sf_buf_free(sf);
			m = **mp;
			sf = sf_buf_alloc(m, SFB_CPUPRIVATE |
			    (md_malloc_wait ? 0 : SFB_NOWAIT));
			if (sf == NULL) {
				error = ENOMEM;
				break;
			}
		}
		p = (char *)sf_buf_kva(sf) + *ma_offs;
		switch (op) {
		case MD_MALLOC_MOVE_ZERO:
			bzero(p, sz);
			break;
		case MD_MALLOC_MOVE_FILL:
			memset(p, fill, sz);
			break;
		case MD_MALLOC_MOVE_READ:
			bcopy(ptr, p, sz);
			cpu_flush_dcache(p, sz);
			break;
		case MD_MALLOC_MOVE_WRITE:
			bcopy(p, ptr, sz);
			break;
		case MD_MALLOC_MOVE_CMP:
			for (i = 0; i < sz; i++, p++) {
				if (!first_read) {
					*uc = (u_char)*p;
					first = *p;
					first_read = 1;
				} else if (*p != first) {
					error = EDOOFUS;
					break;
				}
			}
			break;
		default:
			KASSERT(0, ("md_malloc_move_ma unknown op %d\n", op));
			break;
		}
		if (error != 0)
			break;
		*ma_offs += sz;
		*ma_offs %= PAGE_SIZE;
		if (*ma_offs == 0)
			(*mp)++;
		ptr = (char *)ptr + sz;
	}

	if (sf != NULL)
		sf_buf_free(sf);
	sched_unpin();
	if (op == MD_MALLOC_MOVE_CMP && error != 0) {
		*mp = mp1;
		*ma_offs = ma_offs1;
	}
	return (error);
}