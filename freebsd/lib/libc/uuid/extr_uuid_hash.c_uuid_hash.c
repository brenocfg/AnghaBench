#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int time_low; } ;
typedef  TYPE_1__ uuid_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  uuid_s_ok ; 

uint16_t
uuid_hash(const uuid_t *u, uint32_t *status)
{

	if (status)
		*status = uuid_s_ok;

	/*
	 * Use the most frequently changing bits in the UUID as the hash
	 * value. This should yield a good enough distribution...
	 */
	return ((u) ? u->time_low & 0xffff : 0);
}