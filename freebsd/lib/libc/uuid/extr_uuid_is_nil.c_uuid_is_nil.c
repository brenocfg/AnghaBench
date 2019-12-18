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
typedef  int /*<<< orphan*/  uuid_t ;
typedef  scalar_t__ uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ uuid_s_ok ; 

int32_t
uuid_is_nil(const uuid_t *u, uint32_t *status)
{
	const uint32_t *p;

	if (status)
		*status = uuid_s_ok;

	if (!u)
		return (1);

	/*
	 * Pick the largest type that has equivalent alignment constraints
	 * as an UUID and use it to test if the UUID consists of all zeroes.
	 */
	p = (const uint32_t*)u;
	return ((p[0] == 0 && p[1] == 0 && p[2] == 0 && p[3] == 0) ? 1 : 0);
}