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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  UUID_LEN ; 
 scalar_t__ os_get_random (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uuid_make(u8 uuid[UUID_LEN])
{
	if (os_get_random(uuid, UUID_LEN) < 0)
		return -1;

	/* Replace certain bits as specified in rfc4122 or X.667 */
	uuid[6] &= 0x0f; uuid[6] |= (4 << 4);   /* version 4 == random gen */
	uuid[8] &= 0x3f; uuid[8] |= 0x80;

	return 0;
}