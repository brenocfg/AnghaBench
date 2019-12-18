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
struct unicx {int dummy; } ;
struct uni_msg {int dummy; } ;
struct uni_all {int mtype; int /*<<< orphan*/  u; } ;
struct TYPE_2__ {int (* encode ) (struct uni_msg*,int /*<<< orphan*/ *,struct unicx*) ;} ;

/* Variables and functions */
 int stub1 (struct uni_msg*,int /*<<< orphan*/ *,struct unicx*) ; 
 TYPE_1__** uni_msgtable ; 

int
uni_encode(struct uni_msg *msg, struct uni_all *in, struct unicx *cx)
{
	if (in->mtype >= 256)
		return (-1);
	if (uni_msgtable[in->mtype] == NULL)
		return (-3);

	return ((uni_msgtable[in->mtype]->encode)(msg, &in->u, cx));
}