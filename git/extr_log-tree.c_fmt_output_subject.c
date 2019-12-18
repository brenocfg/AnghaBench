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
struct strbuf {int len; } ;
struct rev_info {char* patch_suffix; int nr; scalar_t__ reroll_count; } ;

/* Variables and functions */
 int FORMAT_PATCH_NAME_MAX ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int,...) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 int strlen (char const*) ; 

void fmt_output_subject(struct strbuf *filename,
			const char *subject,
			struct rev_info *info)
{
	const char *suffix = info->patch_suffix;
	int nr = info->nr;
	int start_len = filename->len;
	int max_len = start_len + FORMAT_PATCH_NAME_MAX - (strlen(suffix) + 1);

	if (0 < info->reroll_count)
		strbuf_addf(filename, "v%d-", info->reroll_count);
	strbuf_addf(filename, "%04d-%s", nr, subject);

	if (max_len < filename->len)
		strbuf_setlen(filename, max_len);
	strbuf_addstr(filename, suffix);
}