#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strbuf {char* buf; } ;
struct TYPE_4__ {char* buf; } ;
struct TYPE_3__ {char* buf; } ;
struct mailinfo {int /*<<< orphan*/  output; TYPE_2__ email; TYPE_1__ name; int /*<<< orphan*/  keep_subject; struct strbuf** p_hdr_data; struct strbuf** s_hdr_data; scalar_t__ patch_lines; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_space (struct strbuf*) ; 
 int /*<<< orphan*/  cleanup_subject (struct mailinfo*,struct strbuf*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  handle_from (struct mailinfo*,struct strbuf*) ; 
 char** header ; 
 int /*<<< orphan*/  output_header_lines (int /*<<< orphan*/ ,char*,struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void handle_info(struct mailinfo *mi)
{
	struct strbuf *hdr;
	int i;

	for (i = 0; header[i]; i++) {
		/* only print inbody headers if we output a patch file */
		if (mi->patch_lines && mi->s_hdr_data[i])
			hdr = mi->s_hdr_data[i];
		else if (mi->p_hdr_data[i])
			hdr = mi->p_hdr_data[i];
		else
			continue;

		if (!strcmp(header[i], "Subject")) {
			if (!mi->keep_subject) {
				cleanup_subject(mi, hdr);
				cleanup_space(hdr);
			}
			output_header_lines(mi->output, "Subject", hdr);
		} else if (!strcmp(header[i], "From")) {
			cleanup_space(hdr);
			handle_from(mi, hdr);
			fprintf(mi->output, "Author: %s\n", mi->name.buf);
			fprintf(mi->output, "Email: %s\n", mi->email.buf);
		} else {
			cleanup_space(hdr);
			fprintf(mi->output, "%s: %s\n", header[i], hdr->buf);
		}
	}
	fprintf(mi->output, "\n");
}