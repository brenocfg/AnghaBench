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
struct cert_status {int dummy; } ;
typedef  int /*<<< orphan*/  hx509_validate_ctx ;
typedef  enum critical_flag { ____Placeholder_critical_flag } critical_flag ;
struct TYPE_3__ {int /*<<< orphan*/  critical; } ;
typedef  TYPE_1__ Extension ;

/* Variables and functions */
#define  D_C 132 
 int /*<<< orphan*/  HX509_VALIDATE_F_VALIDATE ; 
#define  M_C 131 
#define  M_N_C 130 
#define  S_C 129 
#define  S_N_C 128 
 int /*<<< orphan*/  _hx509_abort (char*) ; 
 int /*<<< orphan*/  validate_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
check_Null(hx509_validate_ctx ctx,
	   struct cert_status *status,
	   enum critical_flag cf, const Extension *e)
{
    switch(cf) {
    case D_C:
	break;
    case S_C:
	if (!e->critical)
	    validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
			   "\tCritical not set on SHOULD\n");
	break;
    case S_N_C:
	if (e->critical)
	    validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
			   "\tCritical set on SHOULD NOT\n");
	break;
    case M_C:
	if (!e->critical)
	    validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
			   "\tCritical not set on MUST\n");
	break;
    case M_N_C:
	if (e->critical)
	    validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
			   "\tCritical set on MUST NOT\n");
	break;
    default:
	_hx509_abort("internal check_Null state error");
    }
    return 0;
}