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
struct wt_status {int /*<<< orphan*/  fp; int /*<<< orphan*/  prefix; scalar_t__ null_termination; } ;
struct string_list_item {char* string; } ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  WT_STATUS_UNTRACKED ; 
 int /*<<< orphan*/  color (int /*<<< orphan*/ ,struct wt_status*) ; 
 int /*<<< orphan*/  color_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 char* quote_path (char*,int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void wt_shortstatus_other(struct string_list_item *it,
				 struct wt_status *s, const char *sign)
{
	if (s->null_termination) {
		fprintf(stdout, "%s %s%c", sign, it->string, 0);
	} else {
		struct strbuf onebuf = STRBUF_INIT;
		const char *one;
		one = quote_path(it->string, s->prefix, &onebuf);
		color_fprintf(s->fp, color(WT_STATUS_UNTRACKED, s), "%s", sign);
		printf(" %s\n", one);
		strbuf_release(&onebuf);
	}
}