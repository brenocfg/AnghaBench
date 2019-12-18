#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  section; int /*<<< orphan*/  value; scalar_t__ name; } ;
typedef  TYPE_1__ CONF_VALUE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void dump_value_doall_arg(const CONF_VALUE *a, BIO *out)
{
    if (a->name)
        BIO_printf(out, "[%s] %s=%s\n", a->section, a->name, a->value);
    else
        BIO_printf(out, "[[%s]]\n", a->section);
}