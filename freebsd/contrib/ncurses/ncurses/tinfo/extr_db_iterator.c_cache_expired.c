#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_2__ {scalar_t__ name; } ;
typedef  size_t DBDIRS ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 size_t dbdLAST ; 
 scalar_t__ my_time ; 
 TYPE_1__* my_vars ; 
 scalar_t__ time (scalar_t__*) ; 
 scalar_t__ update_getenv (scalar_t__,size_t) ; 

__attribute__((used)) static bool
cache_expired(void)
{
    bool result = FALSE;
    time_t now = time((time_t *) 0);

    if (now > my_time) {
	result = TRUE;
    } else {
	DBDIRS n;
	for (n = (DBDIRS) 0; n < dbdLAST; ++n) {
	    if (my_vars[n].name != 0
		&& update_getenv(my_vars[n].name, n)) {
		result = TRUE;
		break;
	    }
	}
    }
    return result;
}