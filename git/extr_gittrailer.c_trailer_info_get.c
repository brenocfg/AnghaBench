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
struct trailer_info {char const* trailer_start; char const* trailer_end; char** trailers; size_t trailer_nr; int /*<<< orphan*/  blank_line_before_trailer; } ;
struct strbuf {int /*<<< orphan*/ * buf; } ;
struct process_trailer_options {scalar_t__ no_divider; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (char**,size_t,size_t) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  ends_with_blank_line (char const*,int) ; 
 int /*<<< orphan*/  ensure_configured () ; 
 int find_patch_start (char const*) ; 
 int find_separator (char*,int /*<<< orphan*/ ) ; 
 int find_trailer_end (char const*,int) ; 
 int find_trailer_start (char const*,int) ; 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  separators ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_attach (struct strbuf*,char*,int,int) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_list_free (struct strbuf**) ; 
 struct strbuf** strbuf_split_buf (char const*,int,char,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

void trailer_info_get(struct trailer_info *info, const char *str,
		      const struct process_trailer_options *opts)
{
	int patch_start, trailer_end, trailer_start;
	struct strbuf **trailer_lines, **ptr;
	char **trailer_strings = NULL;
	size_t nr = 0, alloc = 0;
	char **last = NULL;

	ensure_configured();

	if (opts->no_divider)
		patch_start = strlen(str);
	else
		patch_start = find_patch_start(str);

	trailer_end = find_trailer_end(str, patch_start);
	trailer_start = find_trailer_start(str, trailer_end);

	trailer_lines = strbuf_split_buf(str + trailer_start,
					 trailer_end - trailer_start,
					 '\n',
					 0);
	for (ptr = trailer_lines; *ptr; ptr++) {
		if (last && isspace((*ptr)->buf[0])) {
			struct strbuf sb = STRBUF_INIT;
			strbuf_attach(&sb, *last, strlen(*last), strlen(*last));
			strbuf_addbuf(&sb, *ptr);
			*last = strbuf_detach(&sb, NULL);
			continue;
		}
		ALLOC_GROW(trailer_strings, nr + 1, alloc);
		trailer_strings[nr] = strbuf_detach(*ptr, NULL);
		last = find_separator(trailer_strings[nr], separators) >= 1
			? &trailer_strings[nr]
			: NULL;
		nr++;
	}
	strbuf_list_free(trailer_lines);

	info->blank_line_before_trailer = ends_with_blank_line(str,
							       trailer_start);
	info->trailer_start = str + trailer_start;
	info->trailer_end = str + trailer_end;
	info->trailers = trailer_strings;
	info->trailer_nr = nr;
}