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
struct uni_unknown {int /*<<< orphan*/  unrec; int /*<<< orphan*/  epref; } ;

/* Variables and functions */
 scalar_t__ IE_ISGOOD (int /*<<< orphan*/ ) ; 

void
copy_msg_unknown(struct uni_unknown *src, struct uni_unknown *dst)
{
	if(IE_ISGOOD(src->epref))
		dst->epref = src->epref;
	if(IE_ISGOOD(src->unrec))
		dst->unrec = src->unrec;
}