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
typedef  int /*<<< orphan*/  au_evname_map_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_GETEVENT ; 
 int /*<<< orphan*/  EINVAL ; 
 int auditon (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  errno ; 

int
audit_get_event(au_evname_map_t *evn_map, size_t sz)
{

	if (sizeof(*evn_map) != sz) {
		errno = EINVAL;
		return (-1);
	}

	return (auditon(A_GETEVENT, evn_map, sz));
}