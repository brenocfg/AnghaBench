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
struct argv_array {char const** argv; int argc; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char const*) ; 
 char* getenv (char const*) ; 

__attribute__((used)) static const char *getenv_safe(struct argv_array *argv, const char *name)
{
	const char *value = getenv(name);

	if (!value)
		return NULL;

	argv_array_push(argv, value);
	return argv->argv[argv->argc - 1];
}