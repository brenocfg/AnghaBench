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
struct wt_status_change_data {int stagemask; } ;
struct wt_status {int /*<<< orphan*/  prefix; scalar_t__ null_termination; int /*<<< orphan*/  fp; } ;
struct string_list_item {char* string; struct wt_status_change_data* util; } ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  WT_STATUS_UNMERGED ; 
 int /*<<< orphan*/  color (int /*<<< orphan*/ ,struct wt_status*) ; 
 int /*<<< orphan*/  color_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 char* quote_path (char*,int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void wt_shortstatus_unmerged(struct string_list_item *it,
			   struct wt_status *s)
{
	struct wt_status_change_data *d = it->util;
	const char *how = "??";

	switch (d->stagemask) {
	case 1: how = "DD"; break; /* both deleted */
	case 2: how = "AU"; break; /* added by us */
	case 3: how = "UD"; break; /* deleted by them */
	case 4: how = "UA"; break; /* added by them */
	case 5: how = "DU"; break; /* deleted by us */
	case 6: how = "AA"; break; /* both added */
	case 7: how = "UU"; break; /* both modified */
	}
	color_fprintf(s->fp, color(WT_STATUS_UNMERGED, s), "%s", how);
	if (s->null_termination) {
		fprintf(stdout, " %s%c", it->string, 0);
	} else {
		struct strbuf onebuf = STRBUF_INIT;
		const char *one;
		one = quote_path(it->string, s->prefix, &onebuf);
		printf(" %s\n", one);
		strbuf_release(&onebuf);
	}
}