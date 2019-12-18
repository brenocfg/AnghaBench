#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strbuf {char* buf; scalar_t__ len; } ;
struct TYPE_3__ {scalar_t__ len; } ;
struct mailinfo {TYPE_1__ inbody_header_accum; int /*<<< orphan*/ * s_hdr_data; scalar_t__ use_scissors; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_inbody_header_accum (struct mailinfo*) ; 
 int /*<<< orphan*/  handle_header (int /*<<< orphan*/ *,struct strbuf const*) ; 
 scalar_t__* header ; 
 int is_format_patch_separator (char*,scalar_t__) ; 
 scalar_t__ is_inbody_header (struct mailinfo*,struct strbuf const*) ; 
 scalar_t__ is_scissors_line (char*) ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ starts_with (char*,char*) ; 
 int /*<<< orphan*/  strbuf_addbuf (TYPE_1__*,struct strbuf const*) ; 
 int /*<<< orphan*/  strbuf_strip_suffix (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,scalar_t__) ; 

__attribute__((used)) static int check_inbody_header(struct mailinfo *mi, const struct strbuf *line)
{
	if (mi->inbody_header_accum.len &&
	    (line->buf[0] == ' ' || line->buf[0] == '\t')) {
		if (mi->use_scissors && is_scissors_line(line->buf)) {
			/*
			 * This is a scissors line; do not consider this line
			 * as a header continuation line.
			 */
			flush_inbody_header_accum(mi);
			return 0;
		}
		strbuf_strip_suffix(&mi->inbody_header_accum, "\n");
		strbuf_addbuf(&mi->inbody_header_accum, line);
		return 1;
	}

	flush_inbody_header_accum(mi);

	if (starts_with(line->buf, ">From") && isspace(line->buf[5]))
		return is_format_patch_separator(line->buf + 1, line->len - 1);
	if (starts_with(line->buf, "[PATCH]") && isspace(line->buf[7])) {
		int i;
		for (i = 0; header[i]; i++)
			if (!strcmp("Subject", header[i])) {
				handle_header(&mi->s_hdr_data[i], line);
				return 1;
			}
		return 0;
	}
	if (is_inbody_header(mi, line)) {
		strbuf_addbuf(&mi->inbody_header_accum, line);
		return 1;
	}
	return 0;
}