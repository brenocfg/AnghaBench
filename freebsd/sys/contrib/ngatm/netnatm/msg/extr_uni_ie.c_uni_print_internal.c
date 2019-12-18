#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct unicx {scalar_t__ multiline; int /*<<< orphan*/  indent; } ;
struct TYPE_4__ {int /*<<< orphan*/  hdr; } ;
struct uni_all {int mtype; TYPE_2__ u; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* print ) (TYPE_2__*,struct unicx*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct unicx*) ; 
 int /*<<< orphan*/  uni_entry (char*,struct unicx*) ; 
 TYPE_1__** uni_msgtable ; 
 int /*<<< orphan*/  uni_print_eol (struct unicx*) ; 
 int /*<<< orphan*/  uni_print_msghdr_internal (int /*<<< orphan*/ *,struct unicx*) ; 
 int /*<<< orphan*/  uni_printf (struct unicx*,char*,...) ; 

__attribute__((used)) static void
uni_print_internal(const struct uni_all *msg, struct unicx *cx)
{
	uni_entry("mtype", cx);
	if(msg->mtype >= 256 || uni_msgtable[msg->mtype] == NULL) {
		uni_printf(cx, "0x%02x(ERROR)", msg->mtype);
	} else {
		uni_printf(cx, "%s", uni_msgtable[msg->mtype]->name);
		uni_print_msghdr_internal(&msg->u.hdr, cx);
		cx->indent++;
		uni_print_eol(cx);
		(*uni_msgtable[msg->mtype]->print)(&msg->u, cx);
		cx->indent--;
	}

	if(cx->multiline == 0)
		uni_printf(cx, "\n");
}