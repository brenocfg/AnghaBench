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
struct net_device {int dummy; } ;
struct ib_device {int dummy; } ;
typedef  enum ib_gid_type { ____Placeholder_ib_gid_type } ib_gid_type ;

/* Variables and functions */
 int ib_cache_gid_find (struct ib_device*,union ib_gid const*,int,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ib_find_cached_gid(struct ib_device *device,
		       const union ib_gid *gid,
		       enum ib_gid_type gid_type,
		       struct net_device *ndev,
		       u8               *port_num,
		       u16              *index)
{
	return ib_cache_gid_find(device, gid, gid_type, ndev, port_num, index);
}