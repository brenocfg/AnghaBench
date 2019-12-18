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
typedef  int /*<<< orphan*/  ucl_object_t ;
struct ucl_parser {int /*<<< orphan*/  const* comments; } ;

/* Variables and functions */

const ucl_object_t *
ucl_parser_get_comments (struct ucl_parser *parser)
{
	if (parser && parser->comments) {
		return parser->comments;
	}

	return NULL;
}