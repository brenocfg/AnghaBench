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
struct inode {int i_flag; } ;

/* Variables and functions */
 int IN_ACCESS ; 
 int IN_CHANGE ; 
 int IN_MODIFIED ; 
 int IN_UPDATE ; 

__attribute__((used)) static bool
sync_doupdate(struct inode *ip)
{

	return ((ip->i_flag & (IN_ACCESS | IN_CHANGE | IN_MODIFIED |
	    IN_UPDATE)) != 0);
}