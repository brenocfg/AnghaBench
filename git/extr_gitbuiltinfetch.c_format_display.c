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
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  compact_format ; 
 int gettext_width (char const*) ; 
 int /*<<< orphan*/  print_compact (struct strbuf*,char const*,char const*) ; 
 int /*<<< orphan*/  print_remote_to_local (struct strbuf*,char const*,char const*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,...) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void format_display(struct strbuf *display, char code,
			   const char *summary, const char *error,
			   const char *remote, const char *local,
			   int summary_width)
{
	int width = (summary_width + strlen(summary) - gettext_width(summary));

	strbuf_addf(display, "%c %-*s ", code, width, summary);
	if (!compact_format)
		print_remote_to_local(display, remote, local);
	else
		print_compact(display, remote, local);
	if (error)
		strbuf_addf(display, "  (%s)", error);
}