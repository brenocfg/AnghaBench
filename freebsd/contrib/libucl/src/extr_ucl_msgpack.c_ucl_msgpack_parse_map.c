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
struct ucl_stack {int /*<<< orphan*/  obj; } ;
struct ucl_parser {int /*<<< orphan*/  cur_obj; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  enum ucl_msgpack_format { ____Placeholder_ucl_msgpack_format } ucl_msgpack_format ;

/* Variables and functions */

__attribute__((used)) static ssize_t
ucl_msgpack_parse_map (struct ucl_parser *parser,
		struct ucl_stack *container, size_t len, enum ucl_msgpack_format fmt,
		const unsigned char *pos, size_t remain)
{
	container->obj = parser->cur_obj;

	return 0;
}