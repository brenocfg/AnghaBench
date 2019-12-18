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
struct TYPE_2__ {char** ng_str; struct TYPE_2__* ng_next; } ;

/* Variables and functions */
 size_t NG_DOM ; 
 size_t NG_HOST ; 
 size_t NG_USER ; 
 TYPE_1__* nextgrp ; 

int
__getnetgrent(char **hostp, char **userp, char **domp)
{
	if (nextgrp) {
		*hostp = nextgrp->ng_str[NG_HOST];
		*userp = nextgrp->ng_str[NG_USER];
		*domp = nextgrp->ng_str[NG_DOM];
		nextgrp = nextgrp->ng_next;
		return (1);
	}
	return (0);
}