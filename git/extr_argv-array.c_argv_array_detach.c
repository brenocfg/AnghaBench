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
struct argv_array {scalar_t__ argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_array_init (struct argv_array*) ; 
 scalar_t__ empty_argv ; 
 char const** xcalloc (int,int) ; 

const char **argv_array_detach(struct argv_array *array)
{
	if (array->argv == empty_argv)
		return xcalloc(1, sizeof(const char *));
	else {
		const char **ret = array->argv;
		argv_array_init(array);
		return ret;
	}
}