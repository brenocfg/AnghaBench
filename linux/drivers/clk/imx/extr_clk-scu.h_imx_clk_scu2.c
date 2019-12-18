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
typedef  int /*<<< orphan*/  u32 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct clk_hw* __imx_clk_scu (char const*,char const* const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct clk_hw *imx_clk_scu2(const char *name, const char * const *parents,
					  int num_parents, u32 rsrc_id, u8 clk_type)
{
	return __imx_clk_scu(name, parents, num_parents, rsrc_id, clk_type);
}