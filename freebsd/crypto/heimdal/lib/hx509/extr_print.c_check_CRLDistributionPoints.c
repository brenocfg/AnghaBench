#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct cert_status {int haveCRLDP; } ;
typedef  int /*<<< orphan*/  hx509_validate_ctx ;
struct TYPE_19__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_5__ heim_any ;
typedef  enum critical_flag { ____Placeholder_critical_flag } critical_flag ;
struct TYPE_22__ {size_t len; TYPE_2__* val; } ;
struct TYPE_17__ {size_t len; int /*<<< orphan*/ * val; } ;
struct TYPE_18__ {TYPE_3__ fullName; } ;
struct TYPE_21__ {int element; TYPE_4__ u; } ;
struct TYPE_15__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_20__ {TYPE_1__ extnValue; } ;
struct TYPE_16__ {TYPE_5__* distributionPoint; } ;
typedef  int /*<<< orphan*/  GeneralName ;
typedef  TYPE_6__ Extension ;
typedef  TYPE_7__ DistributionPointName ;
typedef  TYPE_8__ CRLDistributionPoints ;

/* Variables and functions */
 int /*<<< orphan*/  HX509_VALIDATE_F_VALIDATE ; 
 int /*<<< orphan*/  HX509_VALIDATE_F_VERBOSE ; 
 int /*<<< orphan*/  check_Null (int /*<<< orphan*/ ,struct cert_status*,int,TYPE_6__ const*) ; 
#define  choice_DistributionPointName_fullName 129 
#define  choice_DistributionPointName_nameRelativeToCRLIssuer 128 
 int decode_CRLDistributionPoints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*,size_t*) ; 
 int decode_DistributionPointName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_CRLDistributionPoints (TYPE_8__*) ; 
 int /*<<< orphan*/  free_DistributionPointName (TYPE_7__*) ; 
 int hx509_general_name_unparse (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  validate_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
check_CRLDistributionPoints(hx509_validate_ctx ctx,
			   struct cert_status *status,
			   enum critical_flag cf,
			   const Extension *e)
{
    CRLDistributionPoints dp;
    size_t size;
    int ret;
    size_t i;

    check_Null(ctx, status, cf, e);

    ret = decode_CRLDistributionPoints(e->extnValue.data,
				       e->extnValue.length,
				       &dp, &size);
    if (ret) {
	validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
		       "Decoding CRL Distribution Points failed: %d\n", ret);
	return 1;
    }

    validate_print(ctx, HX509_VALIDATE_F_VERBOSE, "CRL Distribution Points:\n");
    for (i = 0 ; i < dp.len; i++) {
	if (dp.val[i].distributionPoint) {
	    DistributionPointName dpname;
	    heim_any *data = dp.val[i].distributionPoint;
	    size_t j;

	    ret = decode_DistributionPointName(data->data, data->length,
					       &dpname, NULL);
	    if (ret) {
		validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
			       "Failed to parse CRL Distribution Point Name: %d\n", ret);
		continue;
	    }

	    switch (dpname.element) {
	    case choice_DistributionPointName_fullName:
		validate_print(ctx, HX509_VALIDATE_F_VERBOSE, "Fullname:\n");

		for (j = 0 ; j < dpname.u.fullName.len; j++) {
		    char *s;
		    GeneralName *name = &dpname.u.fullName.val[j];

		    ret = hx509_general_name_unparse(name, &s);
		    if (ret == 0 && s != NULL) {
			validate_print(ctx, HX509_VALIDATE_F_VERBOSE, "   %s\n", s);
			free(s);
		    }
		}
		break;
	    case choice_DistributionPointName_nameRelativeToCRLIssuer:
		validate_print(ctx, HX509_VALIDATE_F_VERBOSE,
			       "Unknown nameRelativeToCRLIssuer");
		break;
	    default:
		validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
			       "Unknown DistributionPointName");
		break;
	    }
	    free_DistributionPointName(&dpname);
	}
    }
    free_CRLDistributionPoints(&dp);

    status->haveCRLDP = 1;

    return 0;
}