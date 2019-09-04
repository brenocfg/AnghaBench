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
struct argv_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strip_escapes (char const*,char const*,char const**) ; 

__attribute__((used)) static void parse_argv(struct argv_array *out, const char *arg, const char *service)
{
	while (*arg) {
		char *expanded = strip_escapes(arg, service, &arg);
		if (expanded)
			argv_array_push(out, expanded);
		free(expanded);
	}
}