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
struct wt_status {int no_gettext; int /*<<< orphan*/ * prefix; scalar_t__ relative_paths; scalar_t__ use_color; } ;

/* Variables and functions */
 int /*<<< orphan*/  wt_shortstatus_print (struct wt_status*) ; 

__attribute__((used)) static void wt_porcelain_print(struct wt_status *s)
{
	s->use_color = 0;
	s->relative_paths = 0;
	s->prefix = NULL;
	s->no_gettext = 1;
	wt_shortstatus_print(s);
}