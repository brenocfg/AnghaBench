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
struct TYPE_2__ {void* ahead_behind; void* behind; void* ahead; void* gone; } ;

/* Variables and functions */
 void* _ (char*) ; 
 TYPE_1__ msgs ; 

void setup_ref_filter_porcelain_msg(void)
{
	msgs.gone = _("gone");
	msgs.ahead = _("ahead %d");
	msgs.behind = _("behind %d");
	msgs.ahead_behind = _("ahead %d, behind %d");
}