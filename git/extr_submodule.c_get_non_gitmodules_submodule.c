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
struct submodule {char const* path; char const* name; } ;

/* Variables and functions */
 char* default_name_or_path (char const*) ; 
 int /*<<< orphan*/  memset (struct submodule*,int /*<<< orphan*/ ,int) ; 
 struct submodule* xmalloc (int) ; 

__attribute__((used)) static const struct submodule *get_non_gitmodules_submodule(const char *path)
{
	struct submodule *ret = NULL;
	const char *name = default_name_or_path(path);

	if (!name)
		return NULL;

	ret = xmalloc(sizeof(*ret));
	memset(ret, 0, sizeof(*ret));
	ret->path = name;
	ret->name = name;

	return (const struct submodule *) ret;
}