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

/* Variables and functions */
 unsigned long FDT_ERR_NOTFOUND ; 
 int /*<<< orphan*/ * of_get_flat_dt_prop (unsigned long,char*,int*) ; 
 unsigned long of_get_flat_dt_root () ; 
 unsigned long of_get_flat_dt_subnode_by_name (unsigned long,char*) ; 

__attribute__((used)) static const u8 *get_vec5_feature(unsigned int index)
{
	unsigned long root, chosen;
	int size;
	const u8 *vec5;

	root = of_get_flat_dt_root();
	chosen = of_get_flat_dt_subnode_by_name(root, "chosen");
	if (chosen == -FDT_ERR_NOTFOUND)
		return NULL;

	vec5 = of_get_flat_dt_prop(chosen, "ibm,architecture-vec-5", &size);
	if (!vec5)
		return NULL;

	if (size <= index)
		return NULL;

	return vec5 + index;
}