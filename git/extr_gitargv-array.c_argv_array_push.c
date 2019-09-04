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
 int /*<<< orphan*/  argv_array_push_nodup (struct argv_array*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

const char *argv_array_push(struct argv_array *array, const char *value)
{
	argv_array_push_nodup(array, xstrdup(value));
	return array->argv[array->argc - 1];
}