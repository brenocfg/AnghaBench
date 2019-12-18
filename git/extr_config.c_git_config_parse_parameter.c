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
struct strbuf {int len; char* buf; } ;
typedef  scalar_t__ (* config_fn_t ) (char*,char const*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ git_config_parse_key (char*,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_list_free (struct strbuf**) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 struct strbuf** strbuf_split_str (char const*,char,int) ; 
 int /*<<< orphan*/  strbuf_trim (struct strbuf*) ; 

int git_config_parse_parameter(const char *text,
			       config_fn_t fn, void *data)
{
	const char *value;
	char *canonical_name;
	struct strbuf **pair;
	int ret;

	pair = strbuf_split_str(text, '=', 2);
	if (!pair[0])
		return error(_("bogus config parameter: %s"), text);

	if (pair[0]->len && pair[0]->buf[pair[0]->len - 1] == '=') {
		strbuf_setlen(pair[0], pair[0]->len - 1);
		value = pair[1] ? pair[1]->buf : "";
	} else {
		value = NULL;
	}

	strbuf_trim(pair[0]);
	if (!pair[0]->len) {
		strbuf_list_free(pair);
		return error(_("bogus config parameter: %s"), text);
	}

	if (git_config_parse_key(pair[0]->buf, &canonical_name, NULL)) {
		ret = -1;
	} else {
		ret = (fn(canonical_name, value, data) < 0) ? -1 : 0;
		free(canonical_name);
	}
	strbuf_list_free(pair);
	return ret;
}