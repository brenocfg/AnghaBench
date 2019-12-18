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
typedef  union uni_msgall {int dummy; } uni_msgall ;
typedef  int /*<<< orphan*/  u_int ;
struct unicx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  uni_print_init (char*,size_t,struct unicx*) ; 
 int /*<<< orphan*/  uni_print_msg_internal (int /*<<< orphan*/ ,union uni_msgall const*,struct unicx*) ; 

void
uni_print_msg(char *buf, size_t size, u_int mtype, const union uni_msgall *all,
    struct unicx *cx)
{
	uni_print_init(buf, size, cx);
	uni_print_msg_internal(mtype, all, cx);
}