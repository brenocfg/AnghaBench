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
struct TYPE_2__ {struct fst_iface* new_iface; struct fst_iface* old_iface; } ;
struct fst_session {TYPE_1__ data; } ;
struct fst_iface {int dummy; } ;
typedef  scalar_t__ Boolean ;

/* Variables and functions */

void fst_session_set_iface(struct fst_session *s, struct fst_iface *iface,
			   Boolean is_old)
{
	if (is_old)
		s->data.old_iface = iface;
	else
		s->data.new_iface = iface;

}