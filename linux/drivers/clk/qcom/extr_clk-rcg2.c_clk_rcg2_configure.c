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
struct freq_tbl {int dummy; } ;
struct clk_rcg2 {int dummy; } ;

/* Variables and functions */
 int __clk_rcg2_configure (struct clk_rcg2*,struct freq_tbl const*) ; 
 int update_config (struct clk_rcg2*) ; 

__attribute__((used)) static int clk_rcg2_configure(struct clk_rcg2 *rcg, const struct freq_tbl *f)
{
	int ret;

	ret = __clk_rcg2_configure(rcg, f);
	if (ret)
		return ret;

	return update_config(rcg);
}