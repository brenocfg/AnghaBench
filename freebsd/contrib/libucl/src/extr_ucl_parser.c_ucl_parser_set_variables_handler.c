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
typedef  int /*<<< orphan*/  ucl_variable_handler ;
struct ucl_parser {void* var_data; int /*<<< orphan*/  var_handler; } ;

/* Variables and functions */

void
ucl_parser_set_variables_handler (struct ucl_parser *parser,
		ucl_variable_handler handler, void *ud)
{
	parser->var_handler = handler;
	parser->var_data = ud;
}