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
struct ucl_parser {TYPE_1__* chunks; } ;
struct TYPE_2__ {int column; } ;

/* Variables and functions */

unsigned
ucl_parser_get_column(struct ucl_parser *parser)
{
	if (parser == NULL || parser->chunks == NULL) {
		return 0;
	}

	return parser->chunks->column;
}