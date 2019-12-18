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
struct ucl_stack {int dummy; } ;
struct ucl_parser {int /*<<< orphan*/  err; } ;
typedef  int ssize_t ;
typedef  enum ucl_msgpack_format { ____Placeholder_ucl_msgpack_format } ucl_msgpack_format ;

/* Variables and functions */
#define  msgpack_ext16 135 
#define  msgpack_ext32 134 
#define  msgpack_ext8 133 
#define  msgpack_fixext1 132 
#define  msgpack_fixext16 131 
#define  msgpack_fixext2 130 
#define  msgpack_fixext4 129 
#define  msgpack_fixext8 128 
 int /*<<< orphan*/  ucl_create_err (int /*<<< orphan*/ *,char*,unsigned int) ; 

__attribute__((used)) static ssize_t
ucl_msgpack_parse_ignore (struct ucl_parser *parser,
		struct ucl_stack *container, size_t len, enum ucl_msgpack_format fmt,
		const unsigned char *pos, size_t remain)
{
	if (len > remain) {
		return -1;
	}

	switch (fmt) {
	case msgpack_fixext1:
		len = 2;
		break;
	case msgpack_fixext2:
		len = 3;
		break;
	case msgpack_fixext4:
		len = 5;
		break;
	case msgpack_fixext8:
		len = 9;
		break;
	case msgpack_fixext16:
		len = 17;
		break;
	case msgpack_ext8:
	case msgpack_ext16:
	case msgpack_ext32:
		len = len + 1;
		break;
	default:
		ucl_create_err (&parser->err, "bad type: %x", (unsigned)fmt);
		return -1;
	}

	return len;
}