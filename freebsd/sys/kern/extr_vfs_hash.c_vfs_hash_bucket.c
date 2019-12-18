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
typedef  size_t u_int ;
struct vfs_hash_head {int dummy; } ;
struct mount {size_t mnt_hashseed; } ;

/* Variables and functions */
 size_t vfs_hash_mask ; 
 struct vfs_hash_head* vfs_hash_tbl ; 

__attribute__((used)) static struct vfs_hash_head *
vfs_hash_bucket(const struct mount *mp, u_int hash)
{

	return (&vfs_hash_tbl[(hash + mp->mnt_hashseed) & vfs_hash_mask]);
}