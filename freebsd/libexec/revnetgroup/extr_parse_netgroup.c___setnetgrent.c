#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct netgrp {int dummy; } ;
struct TYPE_2__ {char* grname; struct netgrp* gr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __endnetgrent () ; 
 TYPE_1__ grouphead ; 
 scalar_t__ malloc (scalar_t__) ; 
 struct netgrp* nextgrp ; 
 scalar_t__ parse_netgrp (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

void
__setnetgrent(char *group)
{
	/* Sanity check */

	if (group == NULL || !strlen(group))
		return;

	if (grouphead.gr == (struct netgrp *)0 ||
		strcmp(group, grouphead.grname)) {
		__endnetgrent();
		if (parse_netgrp(group))
			__endnetgrent();
		else {
			grouphead.grname = (char *)
				malloc(strlen(group) + 1);
			strcpy(grouphead.grname, group);
		}
	}
	nextgrp = grouphead.gr;
}