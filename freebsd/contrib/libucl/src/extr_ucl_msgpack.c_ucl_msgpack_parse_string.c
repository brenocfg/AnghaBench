#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned char const* sv; } ;
struct TYPE_8__ {size_t len; int flags; int /*<<< orphan*/ ** trash_stack; TYPE_2__ value; } ;
typedef  TYPE_3__ ucl_object_t ;
struct ucl_stack {int dummy; } ;
struct ucl_parser {int flags; TYPE_3__* cur_obj; TYPE_1__* chunks; } ;
typedef  int ssize_t ;
typedef  enum ucl_msgpack_format { ____Placeholder_ucl_msgpack_format } ucl_msgpack_format ;
struct TYPE_6__ {int /*<<< orphan*/  priority; } ;

/* Variables and functions */
 int UCL_OBJECT_BINARY ; 
 int UCL_PARSER_ZEROCOPY ; 
 int /*<<< orphan*/  UCL_STRING ; 
 size_t UCL_TRASH_VALUE ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int msgpack_bin32 ; 
 int msgpack_bin8 ; 
 int /*<<< orphan*/  ucl_copy_value_trash (TYPE_3__*) ; 
 TYPE_3__* ucl_object_new_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
ucl_msgpack_parse_string (struct ucl_parser *parser,
		struct ucl_stack *container, size_t len, enum ucl_msgpack_format fmt,
		const unsigned char *pos, size_t remain)
{
	ucl_object_t *obj;

	if (len > remain) {
		return -1;
	}

	obj = ucl_object_new_full (UCL_STRING, parser->chunks->priority);
	obj->value.sv = pos;
	obj->len = len;

	if (fmt >= msgpack_bin8 && fmt <= msgpack_bin32) {
		obj->flags |= UCL_OBJECT_BINARY;
	}

	if (!(parser->flags & UCL_PARSER_ZEROCOPY)) {
		if (obj->flags & UCL_OBJECT_BINARY) {
			obj->trash_stack[UCL_TRASH_VALUE] = malloc (len);

			if (obj->trash_stack[UCL_TRASH_VALUE] != NULL) {
				memcpy (obj->trash_stack[UCL_TRASH_VALUE], pos, len);
			}
		}
		else {
			ucl_copy_value_trash (obj);
		}
	}

	parser->cur_obj = obj;

	return len;
}