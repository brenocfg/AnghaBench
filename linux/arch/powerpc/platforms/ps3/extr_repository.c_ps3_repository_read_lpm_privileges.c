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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int /*<<< orphan*/  PS3_LPAR_ID_PME ; 
 int /*<<< orphan*/  make_field (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_first_field (char*,int /*<<< orphan*/ ) ; 
 int ps3_repository_read_be_node_id (unsigned int,scalar_t__*) ; 
 int read_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

int ps3_repository_read_lpm_privileges(unsigned int be_index, u64 *lpar,
	u64 *rights)
{
	int result;
	u64 node_id;

	*lpar = 0;
	*rights = 0;
	result = ps3_repository_read_be_node_id(be_index, &node_id);
	return result ? result
		: read_node(PS3_LPAR_ID_PME,
			    make_first_field("be", 0),
			    node_id,
			    make_field("lpm", 0),
			    make_field("priv", 0),
			    lpar, rights);
}