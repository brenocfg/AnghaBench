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
struct wt_status_change_data {int /*<<< orphan*/  stagemask; } ;
struct wt_status {int /*<<< orphan*/  prefix; } ;
struct string_list_item {int /*<<< orphan*/  string; struct wt_status_change_data* util; } ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  WT_STATUS_HEADER ; 
 int /*<<< orphan*/  WT_STATUS_UNMERGED ; 
 char* color (int /*<<< orphan*/ ,struct wt_status*) ; 
 int maxwidth (char* (*) (int /*<<< orphan*/ ),int,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 char* quote_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  status_printf (struct wt_status*,char*,char*) ; 
 int /*<<< orphan*/  status_printf_more (struct wt_status*,char const*,char*,char const*,int,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ strlen (char*) ; 
 int utf8_strwidth (char const*) ; 
 char* wt_status_unmerged_status_string (int /*<<< orphan*/ ) ; 
 char* xmallocz (int) ; 

__attribute__((used)) static void wt_longstatus_print_unmerged_data(struct wt_status *s,
					      struct string_list_item *it)
{
	const char *c = color(WT_STATUS_UNMERGED, s);
	struct wt_status_change_data *d = it->util;
	struct strbuf onebuf = STRBUF_INIT;
	static char *padding;
	static int label_width;
	const char *one, *how;
	int len;

	if (!padding) {
		label_width = maxwidth(wt_status_unmerged_status_string, 1, 7);
		label_width += strlen(" ");
		padding = xmallocz(label_width);
		memset(padding, ' ', label_width);
	}

	one = quote_path(it->string, s->prefix, &onebuf);
	status_printf(s, color(WT_STATUS_HEADER, s), "\t");

	how = wt_status_unmerged_status_string(d->stagemask);
	len = label_width - utf8_strwidth(how);
	status_printf_more(s, c, "%s%.*s%s\n", how, len, padding, one);
	strbuf_release(&onebuf);
}