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
struct git_var {char* (* read ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDENT_STRICT ; 
 struct git_var* git_vars ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 char* stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *read_var(const char *var)
{
	struct git_var *ptr;
	const char *val;
	val = NULL;
	for (ptr = git_vars; ptr->read; ptr++) {
		if (strcmp(var, ptr->name) == 0) {
			val = ptr->read(IDENT_STRICT);
			break;
		}
	}
	return val;
}