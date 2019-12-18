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
typedef  int /*<<< orphan*/  hx509_name ;
typedef  int /*<<< orphan*/  hx509_cert ;
struct TYPE_5__ {int /*<<< orphan*/  serialNumber; int /*<<< orphan*/  issuer; } ;
struct TYPE_6__ {TYPE_1__ issuerAndSerialNumber; int /*<<< orphan*/  subjectKeyIdentifier; } ;
struct TYPE_7__ {TYPE_2__ u; int /*<<< orphan*/  element; } ;
typedef  TYPE_3__ CMSIdentifier ;

/* Variables and functions */
#define  CMS_ID_NAME 129 
#define  CMS_ID_SKI 128 
 int /*<<< orphan*/  _hx509_abort (char*) ; 
 int _hx509_find_extension_subject_key_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _hx509_get_cert (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  choice_CMSIdentifier_issuerAndSerialNumber ; 
 int /*<<< orphan*/  choice_CMSIdentifier_subjectKeyIdentifier ; 
 int hx509_cert_get_issuer (int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 
 int hx509_cert_get_serialnumber (int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_name_free (int /*<<< orphan*/ *) ; 
 int hx509_name_to_Name (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fill_CMSIdentifier(const hx509_cert cert,
		   int type,
		   CMSIdentifier *id)
{
    int ret;

    switch (type) {
    case CMS_ID_SKI:
	id->element = choice_CMSIdentifier_subjectKeyIdentifier;
	ret = _hx509_find_extension_subject_key_id(_hx509_get_cert(cert),
						   &id->u.subjectKeyIdentifier);
	if (ret == 0)
	    break;
	/* FALL THOUGH */
    case CMS_ID_NAME: {
	hx509_name name;

	id->element = choice_CMSIdentifier_issuerAndSerialNumber;
	ret = hx509_cert_get_issuer(cert, &name);
	if (ret)
	    return ret;
	ret = hx509_name_to_Name(name, &id->u.issuerAndSerialNumber.issuer);
	hx509_name_free(&name);
	if (ret)
	    return ret;

	ret = hx509_cert_get_serialnumber(cert, &id->u.issuerAndSerialNumber.serialNumber);
	break;
    }
    default:
	_hx509_abort("CMS fill identifier with unknown type");
    }
    return ret;
}