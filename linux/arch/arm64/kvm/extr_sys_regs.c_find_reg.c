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
typedef  int /*<<< orphan*/  table ;
struct sys_reg_params {int dummy; } ;
struct sys_reg_desc {int dummy; } ;

/* Variables and functions */
 struct sys_reg_desc const* bsearch (void*,struct sys_reg_desc const*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_sys_reg ; 
 unsigned long reg_to_encoding (struct sys_reg_params const*) ; 

__attribute__((used)) static const struct sys_reg_desc *find_reg(const struct sys_reg_params *params,
					 const struct sys_reg_desc table[],
					 unsigned int num)
{
	unsigned long pval = reg_to_encoding(params);

	return bsearch((void *)pval, table, num, sizeof(table[0]), match_sys_reg);
}