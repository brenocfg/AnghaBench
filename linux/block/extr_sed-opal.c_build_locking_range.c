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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ LOCKING_RANGE_NON_GLOBAL ; 
 size_t OPAL_LOCKINGRANGE_GLOBAL ; 
 size_t OPAL_UID_LENGTH ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * opaluid ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int build_locking_range(u8 *buffer, size_t length, u8 lr)
{
	if (length > OPAL_UID_LENGTH) {
		pr_debug("Can't build locking range. Length OOB\n");
		return -ERANGE;
	}

	memcpy(buffer, opaluid[OPAL_LOCKINGRANGE_GLOBAL], OPAL_UID_LENGTH);

	if (lr == 0)
		return 0;

	buffer[5] = LOCKING_RANGE_NON_GLOBAL;
	buffer[7] = lr;

	return 0;
}