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
struct cert_status {int isca; } ;
typedef  int /*<<< orphan*/  hx509_validate_ctx ;
typedef  enum critical_flag { ____Placeholder_critical_flag } critical_flag ;
struct TYPE_10__ {scalar_t__* cA; int /*<<< orphan*/ * pathLenConstraint; } ;
struct TYPE_8__ {size_t length; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {int /*<<< orphan*/  critical; TYPE_1__ extnValue; } ;
typedef  TYPE_2__ Extension ;
typedef  TYPE_3__ BasicConstraints ;

/* Variables and functions */
 int /*<<< orphan*/  HX509_VALIDATE_F_VALIDATE ; 
 int /*<<< orphan*/  HX509_VALIDATE_F_VERBOSE ; 
 int /*<<< orphan*/  check_Null (int /*<<< orphan*/ ,struct cert_status*,int,TYPE_2__ const*) ; 
 int decode_BasicConstraints (int /*<<< orphan*/ ,size_t,TYPE_3__*,size_t*) ; 
 int /*<<< orphan*/  free_BasicConstraints (TYPE_3__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  validate_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
check_basicConstraints(hx509_validate_ctx ctx,
		       struct cert_status *status,
		       enum critical_flag cf,
		       const Extension *e)
{
    BasicConstraints b;
    size_t size;
    int ret;

    check_Null(ctx, status, cf, e);

    ret = decode_BasicConstraints(e->extnValue.data, e->extnValue.length,
				  &b, &size);
    if (ret) {
	printf("\tret = %d while decoding BasicConstraints\n", ret);
	return 0;
    }
    if (size != e->extnValue.length)
	printf("\tlength of der data isn't same as extension\n");

    validate_print(ctx, HX509_VALIDATE_F_VERBOSE,
		   "\tis %sa CA\n", b.cA && *b.cA ? "" : "NOT ");
    if (b.pathLenConstraint)
	validate_print(ctx, HX509_VALIDATE_F_VERBOSE,
		       "\tpathLenConstraint: %d\n", *b.pathLenConstraint);

    if (b.cA) {
	if (*b.cA) {
	    if (!e->critical)
		validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
			       "Is a CA and not BasicConstraints CRITICAL\n");
	    status->isca = 1;
	}
	else
	    validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
			   "cA is FALSE, not allowed to be\n");
    }
    free_BasicConstraints(&b);

    return 0;
}