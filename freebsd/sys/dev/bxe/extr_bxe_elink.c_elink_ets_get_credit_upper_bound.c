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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_MAXVAL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELINK_MAX_PACKET_SIZE ; 

__attribute__((used)) static uint32_t elink_ets_get_credit_upper_bound(const uint32_t min_w_val)
{
	const uint32_t credit_upper_bound = (uint32_t)ELINK_MAXVAL((150 * min_w_val),
						ELINK_MAX_PACKET_SIZE);
	return credit_upper_bound;
}