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
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ib_device {int dummy; } ;
struct find_gid_index_context {int gid_type; int /*<<< orphan*/  vlan_id; } ;
typedef  enum ib_gid_type { ____Placeholder_ib_gid_type } ib_gid_type ;

/* Variables and functions */
 int /*<<< orphan*/  find_gid_index ; 
 int ib_find_gid_by_filter (struct ib_device*,union ib_gid const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct find_gid_index_context*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_sgid_index_from_eth(struct ib_device *device, u8 port_num,
				   u16 vlan_id, const union ib_gid *sgid,
				   enum ib_gid_type gid_type,
				   u16 *gid_index)
{
	struct find_gid_index_context context = {.vlan_id = vlan_id,
						 .gid_type = gid_type};

	return ib_find_gid_by_filter(device, sgid, port_num, find_gid_index,
				     &context, gid_index);
}