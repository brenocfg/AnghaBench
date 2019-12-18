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
struct argv_array {char const** argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char*) ; 
 int /*<<< orphan*/  argv_array_pushv (struct argv_array*,char const**) ; 

const char **prepare_git_cmd(struct argv_array *out, const char **argv)
{
	argv_array_push(out, "git");
	argv_array_pushv(out, argv);
	return out->argv;
}