#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int dummy; } ;
struct TYPE_6__ {int nr; TYPE_1__* items; } ;
struct list_objects_filter_options {TYPE_2__ filter_spec; } ;
struct TYPE_5__ {char const* string; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  strbuf_add_separated_string_list (struct strbuf*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_list_append (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_clear (TYPE_2__*,int /*<<< orphan*/ ) ; 

const char *list_objects_filter_spec(struct list_objects_filter_options *filter)
{
	if (!filter->filter_spec.nr)
		BUG("no filter_spec available for this filter");
	if (filter->filter_spec.nr != 1) {
		struct strbuf concatted = STRBUF_INIT;
		strbuf_add_separated_string_list(
			&concatted, "", &filter->filter_spec);
		string_list_clear(&filter->filter_spec, /*free_util=*/0);
		string_list_append(
			&filter->filter_spec, strbuf_detach(&concatted, NULL));
	}

	return filter->filter_spec.items[0].string;
}