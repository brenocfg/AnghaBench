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
struct unicx {scalar_t__ errcnt; } ;
struct uni_msg {int dummy; } ;
struct uni_all {int mtype; int /*<<< orphan*/  u; } ;

/* Variables and functions */
 int uni_decode_body_internal (size_t,struct uni_msg*,int /*<<< orphan*/ *,struct unicx*) ; 
 int /*<<< orphan*/ ** uni_msgtable ; 

int
uni_decode_body(struct uni_msg *msg, struct uni_all *out, struct unicx *cx)
{
	cx->errcnt = 0;
	if (out->mtype >= 256)
		return (-1);
	if (uni_msgtable[out->mtype] == NULL)
		return (-1);
	return (uni_decode_body_internal(out->mtype, msg, &out->u, cx));
}