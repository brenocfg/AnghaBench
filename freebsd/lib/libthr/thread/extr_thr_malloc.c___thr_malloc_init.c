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

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  _thr_umutex_init (int /*<<< orphan*/ *) ; 
 int getpagesizes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ *) ; 
 int npagesizes ; 
 int /*<<< orphan*/ * pagesizes ; 
 int /*<<< orphan*/ * pagesizes_d ; 
 int /*<<< orphan*/  thr_malloc_umtx ; 

void
__thr_malloc_init(void)
{

	if (npagesizes != 0)
		return;
	npagesizes = getpagesizes(pagesizes_d, nitems(pagesizes_d));
	if (npagesizes == -1) {
		npagesizes = 1;
		pagesizes_d[0] = PAGE_SIZE;
	}
	pagesizes = pagesizes_d;
	_thr_umutex_init(&thr_malloc_umtx);
}