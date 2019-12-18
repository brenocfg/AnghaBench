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
typedef  int /*<<< orphan*/  u_int ;
struct timecounter {int /*<<< orphan*/  tc_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  epit_read_counter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
epit_tc_get_timecount(struct timecounter *tc)
{

	return (epit_read_counter(tc->tc_priv));
}