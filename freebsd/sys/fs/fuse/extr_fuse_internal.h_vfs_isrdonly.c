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
struct mount {int mnt_flag; } ;

/* Variables and functions */
 int MNT_RDONLY ; 

__attribute__((used)) static inline bool
vfs_isrdonly(struct mount *mp)
{
	return ((mp->mnt_flag & MNT_RDONLY) != 0);
}