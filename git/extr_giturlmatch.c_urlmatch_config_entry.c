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
struct urlmatch_item {int /*<<< orphan*/  member_0; } ;
struct url_info {int dummy; } ;
struct urlmatch_config {char const* section; int (* cascade_fn ) (char const*,char const*,void*) ;int (* collect_fn ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  cb; int /*<<< orphan*/  vars; scalar_t__ key; struct url_info url; } ;
struct string_list_item {scalar_t__ util; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  matched ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 scalar_t__ cmp_matches (struct urlmatch_item*,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 int match_urls (struct url_info*,struct url_info*,struct urlmatch_item*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct urlmatch_item*,int) ; 
 int /*<<< orphan*/  skip_prefix (char const*,char const*,char const**) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ strcmp (char const*,scalar_t__) ; 
 struct string_list_item* string_list_insert (int /*<<< orphan*/ *,char const*) ; 
 char* strrchr (char const*,char) ; 
 int stub1 (char const*,char const*,void*) ; 
 int stub2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 char* url_normalize_1 (char*,struct url_info*,int) ; 
 scalar_t__ xcalloc (int,int) ; 
 char* xmemdupz (char const*,int) ; 

int urlmatch_config_entry(const char *var, const char *value, void *cb)
{
	struct string_list_item *item;
	struct urlmatch_config *collect = cb;
	struct urlmatch_item matched = {0};
	struct url_info *url = &collect->url;
	const char *key, *dot;
	struct strbuf synthkey = STRBUF_INIT;
	int retval;

	if (!skip_prefix(var, collect->section, &key) || *(key++) != '.') {
		if (collect->cascade_fn)
			return collect->cascade_fn(var, value, cb);
		return 0; /* not interested */
	}
	dot = strrchr(key, '.');
	if (dot) {
		char *config_url, *norm_url;
		struct url_info norm_info;

		config_url = xmemdupz(key, dot - key);
		norm_url = url_normalize_1(config_url, &norm_info, 1);
		free(config_url);
		if (!norm_url)
			return 0;
		retval = match_urls(url, &norm_info, &matched);
		free(norm_url);
		if (!retval)
			return 0;
		key = dot + 1;
	}

	if (collect->key && strcmp(key, collect->key))
		return 0;

	item = string_list_insert(&collect->vars, key);
	if (!item->util) {
		item->util = xcalloc(1, sizeof(matched));
	} else {
		if (cmp_matches(&matched, item->util) < 0)
			 /*
			  * Our match is worse than the old one,
			  * we cannot use it.
			  */
			return 0;
		/* Otherwise, replace it with this one. */
	}

	memcpy(item->util, &matched, sizeof(matched));
	strbuf_addstr(&synthkey, collect->section);
	strbuf_addch(&synthkey, '.');
	strbuf_addstr(&synthkey, key);
	retval = collect->collect_fn(synthkey.buf, value, collect->cb);

	strbuf_release(&synthkey);
	return retval;
}