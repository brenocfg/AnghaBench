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
struct json_writer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jw_array_string (struct json_writer*,char const*) ; 

void jw_array_argc_argv(struct json_writer *jw, int argc, const char **argv)
{
	int k;

	for (k = 0; k < argc; k++)
		jw_array_string(jw, argv[k]);
}