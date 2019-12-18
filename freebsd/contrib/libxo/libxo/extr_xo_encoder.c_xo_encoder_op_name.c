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
typedef  int xo_encoder_op_t ;
typedef  int /*<<< orphan*/  names ;

/* Variables and functions */

const char *
xo_encoder_op_name (xo_encoder_op_t op)
{
    static const char *names[] = {
	/*  0 */ "unknown",
	/*  1 */ "create",
	/*  2 */ "open_container",
	/*  3 */ "close_container",
	/*  4 */ "open_list",
	/*  5 */ "close_list",
	/*  6 */ "open_leaf_list",
	/*  7 */ "close_leaf_list",
	/*  8 */ "open_instance",
	/*  9 */ "close_instance",
	/* 10 */ "string",
	/* 11 */ "content",
	/* 12 */ "finish",
	/* 13 */ "flush",
	/* 14 */ "destroy",
	/* 15 */ "attr",
	/* 16 */ "version",
	/* 17 */ "options",
    };

    if (op > sizeof(names) / sizeof(names[0]))
	return "unknown";

    return names[op];
}