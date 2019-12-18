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
typedef  int /*<<< orphan*/  ucl_object_t ;
struct ucl_stack {int dummy; } ;
struct ucl_parser {int /*<<< orphan*/ * cur_obj; TYPE_1__* chunks; } ;
typedef  int ssize_t ;
typedef  enum ucl_msgpack_format { ____Placeholder_ucl_msgpack_format } ucl_msgpack_format ;
struct TYPE_2__ {int /*<<< orphan*/  priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCL_NULL ; 
 int /*<<< orphan*/ * ucl_object_new_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
ucl_msgpack_parse_null (struct ucl_parser *parser,
		struct ucl_stack *container, size_t len, enum ucl_msgpack_format fmt,
		const unsigned char *pos, size_t remain)
{
	ucl_object_t *obj;

	if (len > remain) {
		return -1;
	}

	obj = ucl_object_new_full (UCL_NULL, parser->chunks->priority);
	parser->cur_obj = obj;

	return 1;
}