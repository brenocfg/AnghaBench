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
struct uni_restart {int /*<<< orphan*/  unrec; int /*<<< orphan*/  restart; int /*<<< orphan*/  connid; } ;

/* Variables and functions */
 scalar_t__ IE_ISGOOD (int /*<<< orphan*/ ) ; 

void
copy_msg_restart(struct uni_restart *src, struct uni_restart *dst)
{
	if(IE_ISGOOD(src->connid))
		dst->connid = src->connid;
	if(IE_ISGOOD(src->restart))
		dst->restart = src->restart;
	if(IE_ISGOOD(src->unrec))
		dst->unrec = src->unrec;
}