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
struct strbuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct mailinfo {int input_error; int /*<<< orphan*/ * patchfile; TYPE_1__ log_message; void* p_hdr_data; int /*<<< orphan*/  input; void* s_hdr_data; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  MAX_HDR_PARSED ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  check_header (struct mailinfo*,struct strbuf*,void*,int) ; 
 int error (char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ ) ; 
 void* fopen (char const*,char*) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_body (struct mailinfo*,struct strbuf*) ; 
 int /*<<< orphan*/  handle_info (struct mailinfo*) ; 
 scalar_t__ isspace (int) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 scalar_t__ read_one_header_line (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ ) ; 
 void* xcalloc (int /*<<< orphan*/ ,int) ; 

int mailinfo(struct mailinfo *mi, const char *msg, const char *patch)
{
	FILE *cmitmsg;
	int peek;
	struct strbuf line = STRBUF_INIT;

	cmitmsg = fopen(msg, "w");
	if (!cmitmsg) {
		perror(msg);
		return -1;
	}
	mi->patchfile = fopen(patch, "w");
	if (!mi->patchfile) {
		perror(patch);
		fclose(cmitmsg);
		return -1;
	}

	mi->p_hdr_data = xcalloc(MAX_HDR_PARSED, sizeof(*(mi->p_hdr_data)));
	mi->s_hdr_data = xcalloc(MAX_HDR_PARSED, sizeof(*(mi->s_hdr_data)));

	do {
		peek = fgetc(mi->input);
		if (peek == EOF) {
			fclose(cmitmsg);
			return error("empty patch: '%s'", patch);
		}
	} while (isspace(peek));
	ungetc(peek, mi->input);

	/* process the email header */
	while (read_one_header_line(&line, mi->input))
		check_header(mi, &line, mi->p_hdr_data, 1);

	handle_body(mi, &line);
	fwrite(mi->log_message.buf, 1, mi->log_message.len, cmitmsg);
	fclose(cmitmsg);
	fclose(mi->patchfile);

	handle_info(mi);
	strbuf_release(&line);
	return mi->input_error;
}