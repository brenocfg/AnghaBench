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
typedef  int /*<<< orphan*/  princ ;
typedef  int /*<<< orphan*/  kvno_str ;
typedef  int /*<<< orphan*/  krb5_keytab ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_enctype ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_const_principal ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_enctype_to_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  krb5_kt_get_full_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  krb5_unparse_name_fixed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

krb5_error_code
_krb5_kt_principal_not_found(krb5_context context,
			     krb5_error_code ret,
			     krb5_keytab id,
			     krb5_const_principal principal,
			     krb5_enctype enctype,
			     int kvno)
{
    char princ[256], kvno_str[25], *kt_name;
    char *enctype_str = NULL;

    krb5_unparse_name_fixed (context, principal, princ, sizeof(princ));
    krb5_kt_get_full_name (context, id, &kt_name);
    krb5_enctype_to_string(context, enctype, &enctype_str);

    if (kvno)
	snprintf(kvno_str, sizeof(kvno_str), "(kvno %d)", kvno);
    else
	kvno_str[0] = '\0';

    krb5_set_error_message (context, ret,
			    N_("Failed to find %s%s in keytab %s (%s)",
			       "principal, kvno, keytab file, enctype"),
			    princ,
			    kvno_str,
			    kt_name ? kt_name : "unknown keytab",
			    enctype_str ? enctype_str : "unknown enctype");
    free(kt_name);
    free(enctype_str);
    return ret;
}