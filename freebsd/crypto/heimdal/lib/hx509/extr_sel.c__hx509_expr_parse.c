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
struct hx_expr {int dummy; } ;
struct TYPE_2__ {char const* buf; struct hx_expr* expr; int /*<<< orphan*/ * error; scalar_t__ offset; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 TYPE_1__ _hx509_expr_input ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  yyparse () ; 

struct hx_expr *
_hx509_expr_parse(const char *buf)
{
    _hx509_expr_input.buf = buf;
    _hx509_expr_input.length = strlen(buf);
    _hx509_expr_input.offset = 0;
    _hx509_expr_input.expr = NULL;

    if (_hx509_expr_input.error) {
	free(_hx509_expr_input.error);
	_hx509_expr_input.error = NULL;
    }

    yyparse();

    return _hx509_expr_input.expr;
}