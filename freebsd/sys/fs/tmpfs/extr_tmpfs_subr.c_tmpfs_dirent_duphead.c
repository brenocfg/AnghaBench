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
struct tmpfs_dirent {int td_cookie; } ;
typedef  int boolean_t ;

/* Variables and functions */
 int TMPFS_DIRCOOKIE_DUPHEAD ; 

__attribute__((used)) static __inline boolean_t
tmpfs_dirent_duphead(struct tmpfs_dirent *de)
{
	return ((de->td_cookie & TMPFS_DIRCOOKIE_DUPHEAD) != 0);
}