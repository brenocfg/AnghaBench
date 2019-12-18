#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_7__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int /*<<< orphan*/  serialNumber; int /*<<< orphan*/  issuer; } ;
struct TYPE_6__ {TYPE_2__ subjectKeyIdentifier; TYPE_3__ issuerAndSerialNumber; } ;
struct TYPE_9__ {int element; TYPE_1__ u; } ;
typedef  TYPE_2__ KeyIdentifier ;
typedef  TYPE_3__ IssuerAndSerialNumber ;
typedef  TYPE_4__ CMSIdentifier ;

/* Variables and functions */
 int ENOMEM ; 
 int _hx509_Name_to_string (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  asprintf (char**,char*,...) ; 
#define  choice_CMSIdentifier_issuerAndSerialNumber 129 
#define  choice_CMSIdentifier_subjectKeyIdentifier 128 
 int der_print_hex_heim_integer (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hex_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static int
unparse_CMSIdentifier(hx509_context context,
		      CMSIdentifier *id,
		      char **str)
{
    int ret;

    *str = NULL;
    switch (id->element) {
    case choice_CMSIdentifier_issuerAndSerialNumber: {
	IssuerAndSerialNumber *iasn;
	char *serial, *name;

	iasn = &id->u.issuerAndSerialNumber;

	ret = _hx509_Name_to_string(&iasn->issuer, &name);
	if(ret)
	    return ret;
	ret = der_print_hex_heim_integer(&iasn->serialNumber, &serial);
	if (ret) {
	    free(name);
	    return ret;
	}
	asprintf(str, "certificate issued by %s with serial number %s",
		 name, serial);
	free(name);
	free(serial);
	break;
    }
    case choice_CMSIdentifier_subjectKeyIdentifier: {
	KeyIdentifier *ki  = &id->u.subjectKeyIdentifier;
	char *keyid;
	ssize_t len;

	len = hex_encode(ki->data, ki->length, &keyid);
	if (len < 0)
	    return ENOMEM;

	asprintf(str, "certificate with id %s", keyid);
	free(keyid);
	break;
    }
    default:
	asprintf(str, "certificate have unknown CMSidentifier type");
	break;
    }
    if (*str == NULL)
	return ENOMEM;
    return 0;
}