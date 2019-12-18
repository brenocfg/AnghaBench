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
typedef  int /*<<< orphan*/ * krb5_keytab ;
typedef  scalar_t__ krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 scalar_t__ krb5_kt_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/ * ktutil_open_keytab () ; 

int
kt_destroy (void *opt, int argc, char **argv)
{
    krb5_error_code ret;
    krb5_keytab keytab;

    if((keytab = ktutil_open_keytab()) == NULL)
	return 1;

    ret = krb5_kt_destroy (context, keytab);
    if (ret) {
	krb5_warn (context, ret, "destroy keytab failed");
	return 1;
    }

    return 0;
}