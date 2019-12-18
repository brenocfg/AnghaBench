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
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int NUMA_NO_NODE ; 
 int associativity_to_nid (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * of_get_associativity (struct device_node*) ; 

__attribute__((used)) static int of_node_to_nid_single(struct device_node *device)
{
	int nid = NUMA_NO_NODE;
	const __be32 *tmp;

	tmp = of_get_associativity(device);
	if (tmp)
		nid = associativity_to_nid(tmp);
	return nid;
}