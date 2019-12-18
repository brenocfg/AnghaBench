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
struct ucl_parser {scalar_t__ state; int /*<<< orphan*/ * top_obj; } ;

/* Variables and functions */
 scalar_t__ UCL_STATE_ERROR ; 
 int /*<<< orphan*/ * ucl_object_ref (int /*<<< orphan*/ *) ; 

ucl_object_t*
ucl_parser_get_object (struct ucl_parser *parser)
{
	if (parser->state != UCL_STATE_ERROR && parser->top_obj != NULL) {
		return ucl_object_ref (parser->top_obj);
	}

	return NULL;
}