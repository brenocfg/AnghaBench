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
typedef  int /*<<< orphan*/  u_int16_t ;
struct agg_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wc_wrreg (struct agg_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wc_wrchctl(struct agg_info *ess, int ch, u_int16_t data)
{
	wc_wrreg(ess, ch << 3, data);
}