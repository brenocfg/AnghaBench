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
struct git_var {char* (* read ) (int /*<<< orphan*/ ) ;char* name; } ;

/* Variables and functions */
 struct git_var* git_vars ; 
 int /*<<< orphan*/  printf (char*,char*,char const*) ; 
 char* stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void list_vars(void)
{
	struct git_var *ptr;
	const char *val;

	for (ptr = git_vars; ptr->read; ptr++)
		if ((val = ptr->read(0)))
			printf("%s=%s\n", ptr->name, val);
}