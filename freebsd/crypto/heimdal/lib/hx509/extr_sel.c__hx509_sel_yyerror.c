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
struct TYPE_2__ {scalar_t__ error; } ;

/* Variables and functions */
 TYPE_1__ _hx509_expr_input ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ strdup (char const*) ; 

void
_hx509_sel_yyerror (const char *s)
{
     if (_hx509_expr_input.error)
         free(_hx509_expr_input.error);

     _hx509_expr_input.error = strdup(s);
}