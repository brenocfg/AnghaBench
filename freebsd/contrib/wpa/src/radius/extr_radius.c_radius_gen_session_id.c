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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int os_get_random (int /*<<< orphan*/ *,size_t) ; 

int radius_gen_session_id(u8 *id, size_t len)
{
	/*
	 * Acct-Session-Id and Acct-Multi-Session-Id should be globally and
	 * temporarily unique. A high quality random number is required
	 * therefore. This could be be improved by switching to a GUID.
	 */
	return os_get_random(id, len);
}