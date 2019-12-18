#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; int ulValueLen; scalar_t__* pValue; } ;
typedef  size_t CK_ULONG ;
typedef  scalar_t__ CK_OBJECT_CLASS ;
typedef  scalar_t__ CK_BBOOL ;
typedef  TYPE_1__ CK_ATTRIBUTE ;

/* Variables and functions */
#define  CKA_APPLICATION 139 
#define  CKA_CLASS 138 
#define  CKA_ID 137 
#define  CKA_LABEL 136 
#define  CKA_PRIVATE 135 
#define  CKA_TOKEN 134 
#define  CKA_VALUE 133 
#define  CKO_CERTIFICATE 132 
#define  CKO_DOMAIN_PARAMETERS 131 
#define  CKO_PRIVATE_KEY 130 
#define  CKO_PUBLIC_KEY 129 
#define  CKO_SECRET_KEY 128 
 int /*<<< orphan*/  application_error (char*) ; 
 int /*<<< orphan*/  st_logf (char*,...) ; 

__attribute__((used)) static void
print_attributes(const CK_ATTRIBUTE *attributes,
		 CK_ULONG num_attributes)
{
    CK_ULONG i;

    st_logf("find objects: attrs: %lu\n", (unsigned long)num_attributes);

    for (i = 0; i < num_attributes; i++) {
	st_logf("  type: ");
	switch (attributes[i].type) {
	case CKA_TOKEN: {
	    CK_BBOOL *ck_true;
	    if (attributes[i].ulValueLen != sizeof(CK_BBOOL)) {
		application_error("token attribute wrong length\n");
		break;
	    }
	    ck_true = attributes[i].pValue;
	    st_logf("token: %s", *ck_true ? "TRUE" : "FALSE");
	    break;
	}
	case CKA_CLASS: {
	    CK_OBJECT_CLASS *class;
	    if (attributes[i].ulValueLen != sizeof(CK_ULONG)) {
		application_error("class attribute wrong length\n");
		break;
	    }
	    class = attributes[i].pValue;
	    st_logf("class ");
	    switch (*class) {
	    case CKO_CERTIFICATE:
		st_logf("certificate");
		break;
	    case CKO_PUBLIC_KEY:
		st_logf("public key");
		break;
	    case CKO_PRIVATE_KEY:
		st_logf("private key");
		break;
	    case CKO_SECRET_KEY:
		st_logf("secret key");
		break;
	    case CKO_DOMAIN_PARAMETERS:
		st_logf("domain parameters");
		break;
	    default:
		st_logf("[class %lx]", (long unsigned)*class);
		break;
	    }
	    break;
	}
	case CKA_PRIVATE:
	    st_logf("private");
	    break;
	case CKA_LABEL:
	    st_logf("label");
	    break;
	case CKA_APPLICATION:
	    st_logf("application");
	    break;
	case CKA_VALUE:
	    st_logf("value");
	    break;
	case CKA_ID:
	    st_logf("id");
	    break;
	default:
	    st_logf("[unknown 0x%08lx]", (unsigned long)attributes[i].type);
	    break;
	}
	st_logf("\n");
    }
}