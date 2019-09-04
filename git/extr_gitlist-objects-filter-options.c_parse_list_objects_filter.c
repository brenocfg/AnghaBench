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
struct list_objects_filter_options {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ gently_parse_list_objects_filter (struct list_objects_filter_options*,char const*,struct strbuf*) ; 

int parse_list_objects_filter(struct list_objects_filter_options *filter_options,
			      const char *arg)
{
	struct strbuf buf = STRBUF_INIT;
	if (gently_parse_list_objects_filter(filter_options, arg, &buf))
		die("%s", buf.buf);
	return 0;
}