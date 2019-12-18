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
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
#define  KRB5_FCC_FVNO_1 131 
#define  KRB5_FCC_FVNO_2 130 
#define  KRB5_FCC_FVNO_3 129 
#define  KRB5_FCC_FVNO_4 128 
 int KRB5_STORAGE_HOST_BYTEORDER ; 
 int KRB5_STORAGE_KEYBLOCK_KEYTYPE_TWICE ; 
 int KRB5_STORAGE_PRINCIPAL_NO_NAME_TYPE ; 
 int KRB5_STORAGE_PRINCIPAL_WRONG_NUM_COMPONENTS ; 
 int /*<<< orphan*/  krb5_abortx (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  krb5_storage_set_flags (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
storage_set_flags(krb5_context context, krb5_storage *sp, int vno)
{
    int flags = 0;
    switch(vno) {
    case KRB5_FCC_FVNO_1:
	flags |= KRB5_STORAGE_PRINCIPAL_WRONG_NUM_COMPONENTS;
	flags |= KRB5_STORAGE_PRINCIPAL_NO_NAME_TYPE;
	flags |= KRB5_STORAGE_HOST_BYTEORDER;
	break;
    case KRB5_FCC_FVNO_2:
	flags |= KRB5_STORAGE_HOST_BYTEORDER;
	break;
    case KRB5_FCC_FVNO_3:
	flags |= KRB5_STORAGE_KEYBLOCK_KEYTYPE_TWICE;
	break;
    case KRB5_FCC_FVNO_4:
	break;
    default:
	krb5_abortx(context,
		    "storage_set_flags called with bad vno (%x)", vno);
    }
    krb5_storage_set_flags(sp, flags);
}