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
struct TYPE_4__ {int initialized; int shutdown; } ;
struct TYPE_3__ {scalar_t__ shutdown; scalar_t__ initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  merge_branch () ; 
 int /*<<< orphan*/  set_gitattributes_to (char*) ; 
 TYPE_2__ test_driver_custom ; 
 TYPE_1__ test_driver_wildcard ; 
 int /*<<< orphan*/  test_drivers_register () ; 
 int /*<<< orphan*/  test_drivers_unregister () ; 

void test_merge_driver__shutdown_is_called(void)
{
    test_driver_custom.initialized = 0;
    test_driver_custom.shutdown = 0;
    test_driver_wildcard.initialized = 0;
    test_driver_wildcard.shutdown = 0;
    
    /* run the merge with the custom driver */
    set_gitattributes_to("custom");
    merge_branch();
    
	/* unregister the drivers, ensure their shutdown function is called */
	test_drivers_unregister();

    /* since the `custom` driver was used, it should have been initialized and
     * shutdown, but the wildcard driver was not used at all and should not
     * have been initialized or shutdown.
     */
	cl_assert(test_driver_custom.initialized);
	cl_assert(test_driver_custom.shutdown);
	cl_assert(!test_driver_wildcard.initialized);
	cl_assert(!test_driver_wildcard.shutdown);

	test_drivers_register();
}