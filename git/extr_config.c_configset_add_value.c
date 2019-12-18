#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct string_list_item {struct key_value_info* util; } ;
struct key_value_info {int linenr; int /*<<< orphan*/  scope; int /*<<< orphan*/  origin_type; int /*<<< orphan*/ * filename; } ;
struct configset_list_item {scalar_t__ value_index; struct config_set_element* e; } ;
struct TYPE_6__ {scalar_t__ nr; } ;
struct config_set_element {TYPE_2__ value_list; int /*<<< orphan*/  ent; int /*<<< orphan*/  key; } ;
struct TYPE_5__ {scalar_t__ nr; struct configset_list_item* items; int /*<<< orphan*/  alloc; } ;
struct config_set {TYPE_1__ list; int /*<<< orphan*/  config_hash; } ;
struct TYPE_7__ {int linenr; int /*<<< orphan*/  origin_type; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct configset_list_item*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  CONFIG_ORIGIN_CMDLINE ; 
 TYPE_4__* cf ; 
 struct config_set_element* configset_find_element (struct config_set*,char const*) ; 
 int /*<<< orphan*/  current_parsing_scope ; 
 int /*<<< orphan*/  hashmap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_entry_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strhash (char const*) ; 
 struct string_list_item* string_list_append_nodup (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_init (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * strintern (scalar_t__) ; 
 void* xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 
 int /*<<< orphan*/  xstrdup_or_null (char const*) ; 

__attribute__((used)) static int configset_add_value(struct config_set *cs, const char *key, const char *value)
{
	struct config_set_element *e;
	struct string_list_item *si;
	struct configset_list_item *l_item;
	struct key_value_info *kv_info = xmalloc(sizeof(*kv_info));

	e = configset_find_element(cs, key);
	/*
	 * Since the keys are being fed by git_config*() callback mechanism, they
	 * are already normalized. So simply add them without any further munging.
	 */
	if (!e) {
		e = xmalloc(sizeof(*e));
		hashmap_entry_init(&e->ent, strhash(key));
		e->key = xstrdup(key);
		string_list_init(&e->value_list, 1);
		hashmap_add(&cs->config_hash, &e->ent);
	}
	si = string_list_append_nodup(&e->value_list, xstrdup_or_null(value));

	ALLOC_GROW(cs->list.items, cs->list.nr + 1, cs->list.alloc);
	l_item = &cs->list.items[cs->list.nr++];
	l_item->e = e;
	l_item->value_index = e->value_list.nr - 1;

	if (!cf)
		BUG("configset_add_value has no source");
	if (cf->name) {
		kv_info->filename = strintern(cf->name);
		kv_info->linenr = cf->linenr;
		kv_info->origin_type = cf->origin_type;
	} else {
		/* for values read from `git_config_from_parameters()` */
		kv_info->filename = NULL;
		kv_info->linenr = -1;
		kv_info->origin_type = CONFIG_ORIGIN_CMDLINE;
	}
	kv_info->scope = current_parsing_scope;
	si->util = kv_info;

	return 0;
}