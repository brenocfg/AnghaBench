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
struct mv64x60_mc_pdata {unsigned int total_mem; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* of_find_node_by_type (int /*<<< orphan*/ *,char*) ; 
 unsigned int* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_total_mem(struct mv64x60_mc_pdata *pdata)
{
	struct device_node *np = NULL;
	const unsigned int *reg;

	np = of_find_node_by_type(NULL, "memory");
	if (!np)
		return;

	reg = of_get_property(np, "reg", NULL);

	pdata->total_mem = reg[1];
}