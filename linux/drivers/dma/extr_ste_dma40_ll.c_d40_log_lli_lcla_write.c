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
struct d40_log_lli {int /*<<< orphan*/  lcsp13; int /*<<< orphan*/  lcsp02; } ;

/* Variables and functions */
 int /*<<< orphan*/  d40_log_lli_link (struct d40_log_lli*,struct d40_log_lli*,int,unsigned int) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void d40_log_lli_lcla_write(struct d40_log_lli *lcla,
			   struct d40_log_lli *lli_dst,
			   struct d40_log_lli *lli_src,
			   int next, unsigned int flags)
{
	d40_log_lli_link(lli_dst, lli_src, next, flags);

	writel_relaxed(lli_src->lcsp02, &lcla[0].lcsp02);
	writel_relaxed(lli_src->lcsp13, &lcla[0].lcsp13);
	writel_relaxed(lli_dst->lcsp02, &lcla[1].lcsp02);
	writel_relaxed(lli_dst->lcsp13, &lcla[1].lcsp13);
}