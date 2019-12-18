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
typedef  int u_int32_t ;
struct finfo {int flag; int forward_xid; } ;

/* Variables and functions */
 struct finfo* FINFO ; 
 int FINFO_ACTIVE ; 
 scalar_t__ NFORWARD ; 

__attribute__((used)) static struct finfo *
forward_find(u_int32_t reply_xid)
{
	int		i;

	i = reply_xid % (u_int32_t)NFORWARD;
	if ((FINFO[i].flag & FINFO_ACTIVE) &&
	    (FINFO[i].forward_xid == reply_xid)) {
		return (&FINFO[i]);
	}
	return (NULL);
}