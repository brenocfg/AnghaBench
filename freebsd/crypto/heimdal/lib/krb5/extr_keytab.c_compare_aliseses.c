#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* aliases; } ;
typedef  TYPE_2__ krb5_keytab_entry ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_const_principal ;
typedef  int /*<<< orphan*/  krb5_boolean ;
struct TYPE_4__ {unsigned int len; int /*<<< orphan*/ * val; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ krb5_principal_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static krb5_boolean
compare_aliseses(krb5_context context,
		 krb5_keytab_entry *entry,
		 krb5_const_principal principal)
{
    unsigned int i;
    if (entry->aliases == NULL)
	return FALSE;
    for (i = 0; i < entry->aliases->len; i++)
	if (krb5_principal_compare(context, &entry->aliases->val[i], principal))
	    return TRUE;
    return FALSE;
}