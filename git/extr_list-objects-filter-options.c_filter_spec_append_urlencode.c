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
struct list_objects_filter_options {int /*<<< orphan*/  filter_spec; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  allow_unencoded ; 
 int /*<<< orphan*/  strbuf_addstr_urlencode (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void filter_spec_append_urlencode(
	struct list_objects_filter_options *filter, const char *raw)
{
	struct strbuf buf = STRBUF_INIT;
	strbuf_addstr_urlencode(&buf, raw, allow_unencoded);
	trace_printf("Add to combine filter-spec: %s\n", buf.buf);
	string_list_append(&filter->filter_spec, strbuf_detach(&buf, NULL));
}