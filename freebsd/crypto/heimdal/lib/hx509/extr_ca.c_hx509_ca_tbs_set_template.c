#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_cert ;
typedef  TYPE_2__* hx509_ca_tbs ;
struct TYPE_10__ {size_t len; int /*<<< orphan*/ * val; } ;
struct TYPE_8__ {int serial; int key; } ;
struct TYPE_9__ {int /*<<< orphan*/  key_usage; TYPE_1__ flags; int /*<<< orphan*/  spki; int /*<<< orphan*/  notAfter; int /*<<< orphan*/  notBefore; int /*<<< orphan*/  serial; scalar_t__ subject; } ;
typedef  int /*<<< orphan*/  KeyUsage ;
typedef  TYPE_3__ ExtKeyUsage ;

/* Variables and functions */
 int HX509_CA_TEMPLATE_EKU ; 
 int HX509_CA_TEMPLATE_KU ; 
 int HX509_CA_TEMPLATE_NOTAFTER ; 
 int HX509_CA_TEMPLATE_NOTBEFORE ; 
 int HX509_CA_TEMPLATE_SERIAL ; 
 int HX509_CA_TEMPLATE_SPKI ; 
 int HX509_CA_TEMPLATE_SUBJECT ; 
 int /*<<< orphan*/  KeyUsage2int (int /*<<< orphan*/ ) ; 
 int _hx509_cert_get_eku (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int _hx509_cert_get_keyusage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  der_free_heim_integer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_ExtKeyUsage (TYPE_3__*) ; 
 int /*<<< orphan*/  free_SubjectPublicKeyInfo (int /*<<< orphan*/ *) ; 
 int hx509_ca_tbs_add_eku (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int hx509_cert_get_SPKI (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_cert_get_notAfter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_cert_get_notBefore (int /*<<< orphan*/ ) ; 
 int hx509_cert_get_serialnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hx509_cert_get_subject (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  hx509_name_free (scalar_t__*) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

int
hx509_ca_tbs_set_template(hx509_context context,
			  hx509_ca_tbs tbs,
			  int flags,
			  hx509_cert cert)
{
    int ret;

    if (flags & HX509_CA_TEMPLATE_SUBJECT) {
	if (tbs->subject)
	    hx509_name_free(&tbs->subject);
	ret = hx509_cert_get_subject(cert, &tbs->subject);
	if (ret) {
	    hx509_set_error_string(context, 0, ret,
				   "Failed to get subject from template");
	    return ret;
	}
    }
    if (flags & HX509_CA_TEMPLATE_SERIAL) {
	der_free_heim_integer(&tbs->serial);
	ret = hx509_cert_get_serialnumber(cert, &tbs->serial);
	tbs->flags.serial = !ret;
	if (ret) {
	    hx509_set_error_string(context, 0, ret,
				   "Failed to copy serial number");
	    return ret;
	}
    }
    if (flags & HX509_CA_TEMPLATE_NOTBEFORE)
	tbs->notBefore = hx509_cert_get_notBefore(cert);
    if (flags & HX509_CA_TEMPLATE_NOTAFTER)
	tbs->notAfter = hx509_cert_get_notAfter(cert);
    if (flags & HX509_CA_TEMPLATE_SPKI) {
	free_SubjectPublicKeyInfo(&tbs->spki);
	ret = hx509_cert_get_SPKI(context, cert, &tbs->spki);
	tbs->flags.key = !ret;
	if (ret)
	    return ret;
    }
    if (flags & HX509_CA_TEMPLATE_KU) {
	KeyUsage ku;
	ret = _hx509_cert_get_keyusage(context, cert, &ku);
	if (ret)
	    return ret;
	tbs->key_usage = KeyUsage2int(ku);
    }
    if (flags & HX509_CA_TEMPLATE_EKU) {
	ExtKeyUsage eku;
	size_t i;
	ret = _hx509_cert_get_eku(context, cert, &eku);
	if (ret)
	    return ret;
	for (i = 0; i < eku.len; i++) {
	    ret = hx509_ca_tbs_add_eku(context, tbs, &eku.val[i]);
	    if (ret) {
		free_ExtKeyUsage(&eku);
		return ret;
	    }
	}
	free_ExtKeyUsage(&eku);
    }
    return 0;
}