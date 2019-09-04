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
typedef  int /*<<< orphan*/  timestamp_t ;
struct ident_split {char* date_end; int /*<<< orphan*/  date_begin; } ;
struct commit {int dummy; } ;
struct author_date_slab {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * author_date_slab_at (struct author_date_slab*,struct commit*) ; 
 char* find_commit_header (char const*,char*,size_t*) ; 
 char* get_commit_buffer (struct commit*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_timestamp (int /*<<< orphan*/ ,char**,int) ; 
 scalar_t__ split_ident_line (struct ident_split*,char const*,size_t) ; 
 int /*<<< orphan*/  unuse_commit_buffer (struct commit*,char const*) ; 

void record_author_date(struct author_date_slab *author_date,
			struct commit *commit)
{
	const char *buffer = get_commit_buffer(commit, NULL);
	struct ident_split ident;
	const char *ident_line;
	size_t ident_len;
	char *date_end;
	timestamp_t date;

	ident_line = find_commit_header(buffer, "author", &ident_len);
	if (!ident_line)
		goto fail_exit; /* no author line */
	if (split_ident_line(&ident, ident_line, ident_len) ||
	    !ident.date_begin || !ident.date_end)
		goto fail_exit; /* malformed "author" line */

	date = parse_timestamp(ident.date_begin, &date_end, 10);
	if (date_end != ident.date_end)
		goto fail_exit; /* malformed date */
	*(author_date_slab_at(author_date, commit)) = date;

fail_exit:
	unuse_commit_buffer(commit, buffer);
}