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
union uni_msgall {int /*<<< orphan*/  hdr; } ;
typedef  int u_int ;
struct unicx {scalar_t__ multiline; int /*<<< orphan*/  indent; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* print ) (union uni_msgall const*,struct unicx*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (union uni_msgall const*,struct unicx*) ; 
 int /*<<< orphan*/  uni_entry (char*,struct unicx*) ; 
 TYPE_1__** uni_msgtable ; 
 int /*<<< orphan*/  uni_print_eol (struct unicx*) ; 
 int /*<<< orphan*/  uni_print_msghdr_internal (int /*<<< orphan*/ *,struct unicx*) ; 
 int /*<<< orphan*/  uni_printf (struct unicx*,char*,...) ; 

__attribute__((used)) static void
uni_print_msg_internal(u_int mtype, const union uni_msgall *msg,
    struct unicx *cx)
{

	uni_entry("mtype", cx);
	if (mtype >= 256 || uni_msgtable[mtype] == NULL) {
		uni_printf(cx, "0x%02x(ERROR)", mtype);
	} else {
		uni_printf(cx, "%s", uni_msgtable[mtype]->name);
		uni_print_msghdr_internal(&msg->hdr, cx);
		cx->indent++;
		uni_print_eol(cx);
		(*uni_msgtable[mtype]->print)(msg, cx);
		cx->indent--;
	}

	if(cx->multiline == 0)
		uni_printf(cx, "\n");
}