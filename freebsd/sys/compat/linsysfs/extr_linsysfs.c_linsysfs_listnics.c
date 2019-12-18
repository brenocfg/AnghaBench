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
struct pfs_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFS_RD ; 
 int /*<<< orphan*/  linsysfs_ifnet_addr ; 
 int /*<<< orphan*/  linsysfs_ifnet_addrlen ; 
 int /*<<< orphan*/  linsysfs_ifnet_flags ; 
 int /*<<< orphan*/  linsysfs_ifnet_ifindex ; 
 int /*<<< orphan*/  linsysfs_ifnet_mtu ; 
 int /*<<< orphan*/  linsysfs_ifnet_tx_queue_len ; 
 int /*<<< orphan*/  linsysfs_ifnet_type ; 
 struct pfs_node* pfs_create_dir (struct pfs_node*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfs_create_file (struct pfs_node*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
linsysfs_listnics(struct pfs_node *dir)
{
	struct pfs_node *nic;
	struct pfs_node *lo;

	nic = pfs_create_dir(dir, "eth0", NULL, NULL, NULL, 0);

	pfs_create_file(nic, "address", &linsysfs_ifnet_addr,
	    NULL, NULL, NULL, PFS_RD);

	pfs_create_file(nic, "addr_len", &linsysfs_ifnet_addrlen,
	    NULL, NULL, NULL, PFS_RD);

	pfs_create_file(nic, "flags", &linsysfs_ifnet_flags,
	    NULL, NULL, NULL, PFS_RD);

	pfs_create_file(nic, "ifindex", &linsysfs_ifnet_ifindex,
	    NULL, NULL, NULL, PFS_RD);

	pfs_create_file(nic, "mtu", &linsysfs_ifnet_mtu,
	    NULL, NULL, NULL, PFS_RD);

	pfs_create_file(nic, "tx_queue_len", &linsysfs_ifnet_tx_queue_len,
	    NULL, NULL, NULL, PFS_RD);

	pfs_create_file(nic, "type", &linsysfs_ifnet_type,
	    NULL, NULL, NULL, PFS_RD);

	lo = pfs_create_dir(dir, "lo", NULL, NULL, NULL, 0);

	pfs_create_file(lo, "address", &linsysfs_ifnet_addr,
	    NULL, NULL, NULL, PFS_RD);

	pfs_create_file(lo, "addr_len", &linsysfs_ifnet_addrlen,
	    NULL, NULL, NULL, PFS_RD);

	pfs_create_file(lo, "flags", &linsysfs_ifnet_flags,
	    NULL, NULL, NULL, PFS_RD);

	pfs_create_file(lo, "ifindex", &linsysfs_ifnet_ifindex,
	    NULL, NULL, NULL, PFS_RD);

	pfs_create_file(lo, "mtu", &linsysfs_ifnet_mtu,
	    NULL, NULL, NULL, PFS_RD);

	pfs_create_file(lo, "tx_queue_len", &linsysfs_ifnet_tx_queue_len,
	    NULL, NULL, NULL, PFS_RD);

	pfs_create_file(lo, "type", &linsysfs_ifnet_type,
	    NULL, NULL, NULL, PFS_RD);
}