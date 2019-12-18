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
typedef  int /*<<< orphan*/  xen_intr_handle_t ;
struct xenisrc {int /*<<< orphan*/ * xi_cookie; int /*<<< orphan*/  xi_vector; } ;
typedef  enum intr_type { ____Placeholder_intr_type } intr_type ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;

/* Variables and functions */
 int EINVAL ; 
 int INTR_EXCL ; 
 int intr_add_handler (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*,int) ; 
 struct xenisrc* xen_intr_isrc (int /*<<< orphan*/ ) ; 

int
xen_intr_add_handler(const char *name, driver_filter_t filter,
    driver_intr_t handler, void *arg, enum intr_type flags,
    xen_intr_handle_t handle)
{
	struct xenisrc *isrc;
	int error;

	isrc = xen_intr_isrc(handle);
	if (isrc == NULL || isrc->xi_cookie != NULL)
		return (EINVAL);

	error = intr_add_handler(name, isrc->xi_vector,filter, handler, arg,
	    flags|INTR_EXCL, &isrc->xi_cookie, 0);
	if (error != 0) {
		printf(
		    "%s: xen_intr_add_handler: intr_add_handler failed: %d\n",
		    name, error);
	}

	return (error);
}