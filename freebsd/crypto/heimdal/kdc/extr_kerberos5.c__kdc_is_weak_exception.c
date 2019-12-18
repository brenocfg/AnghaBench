#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* krb5_principal ;
typedef  scalar_t__ krb5_enctype ;
typedef  int /*<<< orphan*/  krb5_boolean ;
struct TYPE_5__ {scalar_t__ len; int /*<<< orphan*/ * val; } ;
struct TYPE_6__ {TYPE_1__ name_string; } ;
struct TYPE_7__ {TYPE_2__ name; } ;

/* Variables and functions */
 scalar_t__ ETYPE_DES_CBC_CRC ; 
 scalar_t__ ETYPE_DES_CBC_MD4 ; 
 scalar_t__ ETYPE_DES_CBC_MD5 ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

krb5_boolean
_kdc_is_weak_exception(krb5_principal principal, krb5_enctype etype)
{
    if (principal->name.name_string.len > 0 &&
	strcmp(principal->name.name_string.val[0], "afs") == 0 &&
	(etype == ETYPE_DES_CBC_CRC
	 || etype == ETYPE_DES_CBC_MD4
	 || etype == ETYPE_DES_CBC_MD5))
	return TRUE;
    return FALSE;
}