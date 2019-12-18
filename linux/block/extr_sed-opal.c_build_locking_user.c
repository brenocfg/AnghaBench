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
 size_t OPAL_UID_LENGTH ; 
 size_t OPAL_USER1_UID ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * opaluid ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int build_locking_user(u8 *buffer, size_t length, u8 lr)
{
	if (length > OPAL_UID_LENGTH) {
		pr_debug("Can't build locking range user. Length OOB\n");
		return -ERANGE;
	}

	memcpy(buffer, opaluid[OPAL_USER1_UID], OPAL_UID_LENGTH);

	buffer[7] = lr + 1;

	return 0;
}