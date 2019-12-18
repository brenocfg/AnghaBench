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
 int /*<<< orphan*/  _krb5_expand_path_tokens (int /*<<< orphan*/ ,char const*,char**) ; 

krb5_error_code
_krb5_expand_default_cc_name(krb5_context context, const char *str, char **res)
{
    return _krb5_expand_path_tokens(context, str, res);
}