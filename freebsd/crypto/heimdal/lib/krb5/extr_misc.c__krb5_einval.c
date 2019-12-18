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
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  _krb5_debug (int /*<<< orphan*/ ,int,char*,char const*,unsigned long) ; 
 int /*<<< orphan*/  _krb5_debug_backtrace (int /*<<< orphan*/ ) ; 
 scalar_t__ _krb5_have_debug (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,unsigned long) ; 

krb5_error_code
_krb5_einval(krb5_context context, const char *func, unsigned long argn)
{
#ifndef HEIMDAL_SMALLER
    krb5_set_error_message(context, EINVAL,
			   N_("programmer error: invalid argument to %s argument %lu",
			      "function:line"),
			   func, argn);
    if (_krb5_have_debug(context, 10)) {
	_krb5_debug(context, 10, "invalid argument to function %s argument %lu",
		    func, argn);
	_krb5_debug_backtrace(context);
    }
#endif
    return EINVAL;
}