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
struct transport {struct helper_data* data; } ;
struct string_list {int dummy; } ;
struct strbuf {int dummy; } ;
struct helper_data {int /*<<< orphan*/  option; } ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 struct strbuf STRBUF_INIT ; 
 char** boolean_options ; 
 int /*<<< orphan*/  get_helper (struct transport*) ; 
 int /*<<< orphan*/  quote_c_style (char const*,struct strbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int strbuf_set_helper_option (struct helper_data*,struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int string_list_set_helper_option (struct helper_data*,char const*,struct string_list*) ; 
 char** unsupported_options ; 

__attribute__((used)) static int set_helper_option(struct transport *transport,
			  const char *name, const char *value)
{
	struct helper_data *data = transport->data;
	struct strbuf buf = STRBUF_INIT;
	int i, ret, is_bool = 0;

	get_helper(transport);

	if (!data->option)
		return 1;

	if (!strcmp(name, "deepen-not"))
		return string_list_set_helper_option(data, name,
						     (struct string_list *)value);

	for (i = 0; i < ARRAY_SIZE(unsupported_options); i++) {
		if (!strcmp(name, unsupported_options[i]))
			return 1;
	}

	for (i = 0; i < ARRAY_SIZE(boolean_options); i++) {
		if (!strcmp(name, boolean_options[i])) {
			is_bool = 1;
			break;
		}
	}

	strbuf_addf(&buf, "option %s ", name);
	if (is_bool)
		strbuf_addstr(&buf, value ? "true" : "false");
	else
		quote_c_style(value, &buf, NULL, 0);
	strbuf_addch(&buf, '\n');

	ret = strbuf_set_helper_option(data, &buf);
	strbuf_release(&buf);
	return ret;
}