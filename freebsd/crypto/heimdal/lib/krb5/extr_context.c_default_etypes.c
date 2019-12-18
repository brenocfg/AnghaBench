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
typedef  int /*<<< orphan*/  krb5_enctype ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  copy_enctypes (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * krb5_kerberos_enctypes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static krb5_error_code
default_etypes(krb5_context context, krb5_enctype **etype)
{
    const krb5_enctype *p = krb5_kerberos_enctypes(context);
    return copy_enctypes(context, p, etype);
}