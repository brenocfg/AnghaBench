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
typedef  int u32 ;
struct property {int* value; int length; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int be32_to_cpu (int) ; 
 int cpu_to_be32 (int) ; 
 struct property* dlpar_clone_property (struct property*,int) ; 
 scalar_t__ memcmp (int*,int const*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  of_update_property (struct device_node*,struct property*) ; 

__attribute__((used)) static bool find_aa_index(struct device_node *dr_node,
			 struct property *ala_prop,
			 const u32 *lmb_assoc, u32 *aa_index)
{
	u32 *assoc_arrays, new_prop_size;
	struct property *new_prop;
	int aa_arrays, aa_array_entries, aa_array_sz;
	int i, index;

	/*
	 * The ibm,associativity-lookup-arrays property is defined to be
	 * a 32-bit value specifying the number of associativity arrays
	 * followed by a 32-bitvalue specifying the number of entries per
	 * array, followed by the associativity arrays.
	 */
	assoc_arrays = ala_prop->value;

	aa_arrays = be32_to_cpu(assoc_arrays[0]);
	aa_array_entries = be32_to_cpu(assoc_arrays[1]);
	aa_array_sz = aa_array_entries * sizeof(u32);

	for (i = 0; i < aa_arrays; i++) {
		index = (i * aa_array_entries) + 2;

		if (memcmp(&assoc_arrays[index], &lmb_assoc[1], aa_array_sz))
			continue;

		*aa_index = i;
		return true;
	}

	new_prop_size = ala_prop->length + aa_array_sz;
	new_prop = dlpar_clone_property(ala_prop, new_prop_size);
	if (!new_prop)
		return false;

	assoc_arrays = new_prop->value;

	/* increment the number of entries in the lookup array */
	assoc_arrays[0] = cpu_to_be32(aa_arrays + 1);

	/* copy the new associativity into the lookup array */
	index = aa_arrays * aa_array_entries + 2;
	memcpy(&assoc_arrays[index], &lmb_assoc[1], aa_array_sz);

	of_update_property(dr_node, new_prop);

	/*
	 * The associativity lookup array index for this lmb is
	 * number of entries - 1 since we added its associativity
	 * to the end of the lookup array.
	 */
	*aa_index = be32_to_cpu(assoc_arrays[0]) - 1;
	return true;
}