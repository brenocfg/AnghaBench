#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct string_list {int nr; TYPE_1__* items; } ;
struct strbuf {int dummy; } ;
struct helper_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  quote_c_style (int /*<<< orphan*/ ,struct strbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int strbuf_set_helper_option (struct helper_data*,struct strbuf*) ; 

__attribute__((used)) static int string_list_set_helper_option(struct helper_data *data,
					 const char *name,
					 struct string_list *list)
{
	struct strbuf buf = STRBUF_INIT;
	int i, ret = 0;

	for (i = 0; i < list->nr; i++) {
		strbuf_addf(&buf, "option %s ", name);
		quote_c_style(list->items[i].string, &buf, NULL, 0);
		strbuf_addch(&buf, '\n');

		if ((ret = strbuf_set_helper_option(data, &buf)))
			break;
		strbuf_reset(&buf);
	}
	strbuf_release(&buf);
	return ret;
}