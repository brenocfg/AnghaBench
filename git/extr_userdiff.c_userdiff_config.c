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
struct userdiff_driver {int binary; int /*<<< orphan*/  word_regex; int /*<<< orphan*/  textconv_want_cache; int /*<<< orphan*/  textconv; int /*<<< orphan*/  external; int /*<<< orphan*/  funcname; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct userdiff_driver*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_EXTENDED ; 
 struct userdiff_driver* drivers ; 
 int /*<<< orphan*/  drivers_alloc ; 
 int git_config_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  memset (struct userdiff_driver*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ndrivers ; 
 int parse_bool (int /*<<< orphan*/ *,char const*,char const*) ; 
 scalar_t__ parse_config_key (char const*,char*,char const**,int*,char const**) ; 
 int parse_funcname (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ) ; 
 int parse_tristate (int*,char const*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 struct userdiff_driver* userdiff_find_by_namelen (char const*,int) ; 
 int /*<<< orphan*/  xmemdupz (char const*,int) ; 

int userdiff_config(const char *k, const char *v)
{
	struct userdiff_driver *drv;
	const char *name, *type;
	int namelen;

	if (parse_config_key(k, "diff", &name, &namelen, &type) || !name)
		return 0;

	drv = userdiff_find_by_namelen(name, namelen);
	if (!drv) {
		ALLOC_GROW(drivers, ndrivers+1, drivers_alloc);
		drv = &drivers[ndrivers++];
		memset(drv, 0, sizeof(*drv));
		drv->name = xmemdupz(name, namelen);
		drv->binary = -1;
	}

	if (!strcmp(type, "funcname"))
		return parse_funcname(&drv->funcname, k, v, 0);
	if (!strcmp(type, "xfuncname"))
		return parse_funcname(&drv->funcname, k, v, REG_EXTENDED);
	if (!strcmp(type, "binary"))
		return parse_tristate(&drv->binary, k, v);
	if (!strcmp(type, "command"))
		return git_config_string(&drv->external, k, v);
	if (!strcmp(type, "textconv"))
		return git_config_string(&drv->textconv, k, v);
	if (!strcmp(type, "cachetextconv"))
		return parse_bool(&drv->textconv_want_cache, k, v);
	if (!strcmp(type, "wordregex"))
		return git_config_string(&drv->word_regex, k, v);

	return 0;
}