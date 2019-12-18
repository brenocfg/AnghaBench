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
struct wt_status_change_data {char* rename_source; scalar_t__ worktree_status; scalar_t__ index_status; } ;
struct wt_status {int /*<<< orphan*/  prefix; scalar_t__ null_termination; int /*<<< orphan*/  fp; } ;
struct string_list_item {char* string; struct wt_status_change_data* util; } ;
struct strbuf {char* buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  WT_STATUS_CHANGED ; 
 int /*<<< orphan*/  WT_STATUS_UPDATED ; 
 int /*<<< orphan*/  color (int /*<<< orphan*/ ,struct wt_status*) ; 
 int /*<<< orphan*/  color_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 char* quote_path (char*,int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 

__attribute__((used)) static void wt_shortstatus_status(struct string_list_item *it,
			 struct wt_status *s)
{
	struct wt_status_change_data *d = it->util;

	if (d->index_status)
		color_fprintf(s->fp, color(WT_STATUS_UPDATED, s), "%c", d->index_status);
	else
		putchar(' ');
	if (d->worktree_status)
		color_fprintf(s->fp, color(WT_STATUS_CHANGED, s), "%c", d->worktree_status);
	else
		putchar(' ');
	putchar(' ');
	if (s->null_termination) {
		fprintf(stdout, "%s%c", it->string, 0);
		if (d->rename_source)
			fprintf(stdout, "%s%c", d->rename_source, 0);
	} else {
		struct strbuf onebuf = STRBUF_INIT;
		const char *one;

		if (d->rename_source) {
			one = quote_path(d->rename_source, s->prefix, &onebuf);
			if (*one != '"' && strchr(one, ' ') != NULL) {
				putchar('"');
				strbuf_addch(&onebuf, '"');
				one = onebuf.buf;
			}
			printf("%s -> ", one);
			strbuf_release(&onebuf);
		}
		one = quote_path(it->string, s->prefix, &onebuf);
		if (*one != '"' && strchr(one, ' ') != NULL) {
			putchar('"');
			strbuf_addch(&onebuf, '"');
			one = onebuf.buf;
		}
		printf("%s\n", one);
		strbuf_release(&onebuf);
	}
}