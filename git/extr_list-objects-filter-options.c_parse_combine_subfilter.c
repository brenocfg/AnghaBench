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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct list_objects_filter_options {size_t sub_nr; int /*<<< orphan*/ * sub; int /*<<< orphan*/  sub_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW_BY (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ gently_parse_list_objects_filter (int /*<<< orphan*/ *,char*,struct strbuf*) ; 
 scalar_t__ has_reserved_character (struct strbuf*,struct strbuf*) ; 
 char* url_percent_decode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_combine_subfilter(
	struct list_objects_filter_options *filter_options,
	struct strbuf *subspec,
	struct strbuf *errbuf)
{
	size_t new_index = filter_options->sub_nr;
	char *decoded;
	int result;

	ALLOC_GROW_BY(filter_options->sub, filter_options->sub_nr, 1,
		      filter_options->sub_alloc);

	decoded = url_percent_decode(subspec->buf);

	result = has_reserved_character(subspec, errbuf) ||
		gently_parse_list_objects_filter(
			&filter_options->sub[new_index], decoded, errbuf);

	free(decoded);
	return result;
}