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
typedef  int /*<<< orphan*/  krb5_keytab_entry ;
typedef  int /*<<< orphan*/  krb5_keytab ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  entry ;

/* Variables and functions */
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ krb5_kt_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_kt_have_content (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_kt_remove_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_resolve (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
test_empty_keytab(krb5_context context, const char *keytab)
{
    krb5_error_code ret;
    krb5_keytab id;
    krb5_keytab_entry entry;

    ret = krb5_kt_resolve(context, keytab, &id);
    if (ret)
	krb5_err(context, 1, ret, "krb5_kt_resolve");

    memset(&entry, 0, sizeof(entry));

    krb5_kt_remove_entry(context, id, &entry);

    ret = krb5_kt_have_content(context, id);
    if (ret == 0)
	krb5_errx(context, 1, "supposed to be empty keytab isn't");

    ret = krb5_kt_close(context, id);
    if (ret)
	krb5_err(context, 1, ret, "krb5_kt_close");
}