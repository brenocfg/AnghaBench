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
struct sys_reg_desc {int dummy; } ;

/* Variables and functions */
 int reg_to_encoding (struct sys_reg_desc const*) ; 

__attribute__((used)) static int match_sys_reg(const void *key, const void *elt)
{
	const unsigned long pval = (unsigned long)key;
	const struct sys_reg_desc *r = elt;

	return pval - reg_to_encoding(r);
}