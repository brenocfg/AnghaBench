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
struct ucred {int dummy; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  crextend (struct ucred*,int) ; 
 int /*<<< orphan*/  crsetgroups_locked (struct ucred*,int,int /*<<< orphan*/ *) ; 
 int ngroups_max ; 

void
crsetgroups(struct ucred *cr, int ngrp, gid_t *groups)
{

	if (ngrp > ngroups_max + 1)
		ngrp = ngroups_max + 1;

	crextend(cr, ngrp);
	crsetgroups_locked(cr, ngrp, groups);
}