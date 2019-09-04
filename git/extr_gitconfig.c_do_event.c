#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct parse_event_data {int previous_type; size_t previous_offset; TYPE_1__* opts; } ;
typedef  enum config_event_t { ____Placeholder_config_event_t } config_event_t ;
struct TYPE_5__ {size_t (* do_ftell ) (TYPE_2__*) ;} ;
struct TYPE_4__ {scalar_t__ (* event_fn ) (int,size_t,size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  event_fn_data; } ;

/* Variables and functions */
 int CONFIG_EVENT_EOF ; 
 int CONFIG_EVENT_WHITESPACE ; 
 TYPE_2__* cf ; 
 size_t stub1 (TYPE_2__*) ; 
 scalar_t__ stub2 (int,size_t,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_event(enum config_event_t type, struct parse_event_data *data)
{
	size_t offset;

	if (!data->opts || !data->opts->event_fn)
		return 0;

	if (type == CONFIG_EVENT_WHITESPACE &&
	    data->previous_type == type)
		return 0;

	offset = cf->do_ftell(cf);
	/*
	 * At EOF, the parser always "inserts" an extra '\n', therefore
	 * the end offset of the event is the current file position, otherwise
	 * we will already have advanced to the next event.
	 */
	if (type != CONFIG_EVENT_EOF)
		offset--;

	if (data->previous_type != CONFIG_EVENT_EOF &&
	    data->opts->event_fn(data->previous_type, data->previous_offset,
				 offset, data->opts->event_fn_data) < 0)
		return -1;

	data->previous_type = type;
	data->previous_offset = offset;

	return 0;
}