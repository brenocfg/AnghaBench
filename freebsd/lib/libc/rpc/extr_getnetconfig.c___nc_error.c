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
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  nc_key ; 
 scalar_t__ nc_key_error ; 
 int /*<<< orphan*/  nc_key_init ; 
 int /*<<< orphan*/  nc_once ; 
 scalar_t__ thr_getspecific (int /*<<< orphan*/ ) ; 
 scalar_t__ thr_main () ; 
 scalar_t__ thr_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ thr_setspecific (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int *
__nc_error(void)
{
	static int nc_error = 0;
	int *nc_addr;

	/*
	 * Use the static `nc_error' if we are the main thread
	 * (including non-threaded programs), or if an allocation
	 * fails.
	 */
	if (thr_main())
		return (&nc_error);
	if (thr_once(&nc_once, nc_key_init) != 0 || nc_key_error != 0)
		return (&nc_error);
	if ((nc_addr = (int *)thr_getspecific(nc_key)) == NULL) {
		nc_addr = (int *)malloc(sizeof (int));
		if (thr_setspecific(nc_key, (void *) nc_addr) != 0) {
			free(nc_addr);
			return (&nc_error);
		}
		*nc_addr = 0;
	}
	return (nc_addr);
}