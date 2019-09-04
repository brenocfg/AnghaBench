#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct conf_info {int /*<<< orphan*/  if_missing; int /*<<< orphan*/  if_exists; int /*<<< orphan*/  where; void* command; void* key; } ;
struct arg_item {struct conf_info conf; } ;
typedef  enum trailer_info_type { ____Placeholder_trailer_info_type } trailer_info_type ;
struct TYPE_3__ {int type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  BUG (char*,int) ; 
#define  TRAILER_COMMAND 132 
#define  TRAILER_IF_EXISTS 131 
#define  TRAILER_IF_MISSING 130 
#define  TRAILER_KEY 129 
#define  TRAILER_WHERE 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct arg_item* get_conf_item (char*) ; 
 int /*<<< orphan*/  skip_prefix (char const*,char*,char const**) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 char* strrchr (char const*,char) ; 
 TYPE_1__* trailer_config_items ; 
 int /*<<< orphan*/  trailer_set_if_exists (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  trailer_set_if_missing (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  trailer_set_where (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*,...) ; 
 void* xstrdup (char const*) ; 
 char* xstrndup (char const*,int) ; 

__attribute__((used)) static int git_trailer_config(const char *conf_key, const char *value, void *cb)
{
	const char *trailer_item, *variable_name;
	struct arg_item *item;
	struct conf_info *conf;
	char *name = NULL;
	enum trailer_info_type type;
	int i;

	if (!skip_prefix(conf_key, "trailer.", &trailer_item))
		return 0;

	variable_name = strrchr(trailer_item, '.');
	if (!variable_name)
		return 0;

	variable_name++;
	for (i = 0; i < ARRAY_SIZE(trailer_config_items); i++) {
		if (strcmp(trailer_config_items[i].name, variable_name))
			continue;
		name = xstrndup(trailer_item,  variable_name - trailer_item - 1);
		type = trailer_config_items[i].type;
		break;
	}

	if (!name)
		return 0;

	item = get_conf_item(name);
	conf = &item->conf;
	free(name);

	switch (type) {
	case TRAILER_KEY:
		if (conf->key)
			warning(_("more than one %s"), conf_key);
		conf->key = xstrdup(value);
		break;
	case TRAILER_COMMAND:
		if (conf->command)
			warning(_("more than one %s"), conf_key);
		conf->command = xstrdup(value);
		break;
	case TRAILER_WHERE:
		if (trailer_set_where(&conf->where, value))
			warning(_("unknown value '%s' for key '%s'"), value, conf_key);
		break;
	case TRAILER_IF_EXISTS:
		if (trailer_set_if_exists(&conf->if_exists, value))
			warning(_("unknown value '%s' for key '%s'"), value, conf_key);
		break;
	case TRAILER_IF_MISSING:
		if (trailer_set_if_missing(&conf->if_missing, value))
			warning(_("unknown value '%s' for key '%s'"), value, conf_key);
		break;
	default:
		BUG("trailer.c: unhandled type %d", type);
	}
	return 0;
}