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
struct trailer_item {char* value; } ;
struct TYPE_2__ {scalar_t__ command; } ;
struct arg_item {char* value; TYPE_1__ conf; } ;

/* Variables and functions */
 char* apply_command (scalar_t__,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void apply_item_command(struct trailer_item *in_tok, struct arg_item *arg_tok)
{
	if (arg_tok->conf.command) {
		const char *arg;
		if (arg_tok->value && arg_tok->value[0]) {
			arg = arg_tok->value;
		} else {
			if (in_tok && in_tok->value)
				arg = xstrdup(in_tok->value);
			else
				arg = xstrdup("");
		}
		arg_tok->value = apply_command(arg_tok->conf.command, arg);
		free((char *)arg);
	}
}