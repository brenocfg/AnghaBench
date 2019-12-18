#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct rk_strpool {int dummy; } ;
typedef  int /*<<< orphan*/  dir ;
struct TYPE_24__ {unsigned char* data; int length; } ;
struct TYPE_23__ {scalar_t__ data; scalar_t__ length; } ;
struct TYPE_21__ {int /*<<< orphan*/  rdnSequence; } ;
struct TYPE_22__ {TYPE_5__ u; int /*<<< orphan*/  element; } ;
struct TYPE_19__ {scalar_t__ data; scalar_t__ length; } ;
struct TYPE_18__ {scalar_t__ data; scalar_t__ length; } ;
struct TYPE_17__ {int /*<<< orphan*/  type_id; } ;
struct TYPE_25__ {int /*<<< orphan*/  registeredID; TYPE_8__ iPAddress; TYPE_7__ uniformResourceIdentifier; TYPE_6__ directoryName; TYPE_3__ dNSName; TYPE_2__ rfc822Name; TYPE_1__ otherName; } ;
struct TYPE_20__ {int /*<<< orphan*/  rdnSequence; } ;
struct TYPE_16__ {int element; TYPE_9__ u; } ;
struct TYPE_15__ {TYPE_4__ u; int /*<<< orphan*/  element; } ;
typedef  TYPE_10__ Name ;
typedef  TYPE_11__ GeneralName ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int _hx509_unparse_Name (TYPE_10__*,char**) ; 
#define  choice_GeneralName_dNSName 134 
#define  choice_GeneralName_directoryName 133 
#define  choice_GeneralName_iPAddress 132 
#define  choice_GeneralName_otherName 131 
#define  choice_GeneralName_registeredID 130 
#define  choice_GeneralName_rfc822Name 129 
#define  choice_GeneralName_uniformResourceIdentifier 128 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hx509_oid_sprint (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  memset (TYPE_10__*,int /*<<< orphan*/ ,int) ; 
 char* rk_strpoolcollect (struct rk_strpool*) ; 
 struct rk_strpool* rk_strpoolprintf (struct rk_strpool*,char*,...) ; 

int
hx509_general_name_unparse(GeneralName *name, char **str)
{
    struct rk_strpool *strpool = NULL;

    *str = NULL;

    switch (name->element) {
    case choice_GeneralName_otherName: {
	char *oid;
	hx509_oid_sprint(&name->u.otherName.type_id, &oid);
	if (oid == NULL)
	    return ENOMEM;
	strpool = rk_strpoolprintf(strpool, "otherName: %s", oid);
	free(oid);
	break;
    }
    case choice_GeneralName_rfc822Name:
	strpool = rk_strpoolprintf(strpool, "rfc822Name: %.*s\n",
				   (int)name->u.rfc822Name.length,
				   (char *)name->u.rfc822Name.data);
	break;
    case choice_GeneralName_dNSName:
	strpool = rk_strpoolprintf(strpool, "dNSName: %.*s\n",
				   (int)name->u.dNSName.length,
				   (char *)name->u.dNSName.data);
	break;
    case choice_GeneralName_directoryName: {
	Name dir;
	char *s;
	int ret;
	memset(&dir, 0, sizeof(dir));
	dir.element = name->u.directoryName.element;
	dir.u.rdnSequence = name->u.directoryName.u.rdnSequence;
	ret = _hx509_unparse_Name(&dir, &s);
	if (ret)
	    return ret;
	strpool = rk_strpoolprintf(strpool, "directoryName: %s", s);
	free(s);
	break;
    }
    case choice_GeneralName_uniformResourceIdentifier:
	strpool = rk_strpoolprintf(strpool, "URI: %.*s",
				   (int)name->u.uniformResourceIdentifier.length,
				   (char *)name->u.uniformResourceIdentifier.data);
	break;
    case choice_GeneralName_iPAddress: {
	unsigned char *a = name->u.iPAddress.data;

	strpool = rk_strpoolprintf(strpool, "IPAddress: ");
	if (strpool == NULL)
	    break;
	if (name->u.iPAddress.length == 4)
	    strpool = rk_strpoolprintf(strpool, "%d.%d.%d.%d",
				       a[0], a[1], a[2], a[3]);
	else if (name->u.iPAddress.length == 16)
	    strpool = rk_strpoolprintf(strpool,
				       "%02X:%02X:%02X:%02X:"
				       "%02X:%02X:%02X:%02X:"
				       "%02X:%02X:%02X:%02X:"
				       "%02X:%02X:%02X:%02X",
				       a[0], a[1], a[2], a[3],
				       a[4], a[5], a[6], a[7],
				       a[8], a[9], a[10], a[11],
				       a[12], a[13], a[14], a[15]);
	else
	    strpool = rk_strpoolprintf(strpool,
				       "unknown IP address of length %lu",
				       (unsigned long)name->u.iPAddress.length);
	break;
    }
    case choice_GeneralName_registeredID: {
	char *oid;
	hx509_oid_sprint(&name->u.registeredID, &oid);
	if (oid == NULL)
	    return ENOMEM;
	strpool = rk_strpoolprintf(strpool, "registeredID: %s", oid);
	free(oid);
	break;
    }
    default:
	return EINVAL;
    }
    if (strpool == NULL)
	return ENOMEM;

    *str = rk_strpoolcollect(strpool);

    return 0;
}