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
struct unicx {int dummy; } ;
struct uni_msghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  uni_print_init (char*,size_t,struct unicx*) ; 
 int /*<<< orphan*/  uni_print_msghdr_internal (struct uni_msghdr const*,struct unicx*) ; 

void
uni_print_msghdr(char *str, size_t len, const struct uni_msghdr *hdr,
    struct unicx *cx)
{
	uni_print_init(str, len, cx);
	uni_print_msghdr_internal(hdr, cx);
}