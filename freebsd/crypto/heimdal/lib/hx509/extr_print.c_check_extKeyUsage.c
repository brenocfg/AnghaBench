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
struct cert_status {int dummy; } ;
typedef  int /*<<< orphan*/  hx509_validate_ctx ;
typedef  enum critical_flag { ____Placeholder_critical_flag } critical_flag ;
struct TYPE_10__ {size_t len; int /*<<< orphan*/ * val; } ;
struct TYPE_8__ {size_t length; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {TYPE_1__ extnValue; } ;
typedef  TYPE_2__ Extension ;
typedef  TYPE_3__ ExtKeyUsage ;

/* Variables and functions */
 int /*<<< orphan*/  HX509_VALIDATE_F_VALIDATE ; 
 int /*<<< orphan*/  HX509_VALIDATE_F_VERBOSE ; 
 int /*<<< orphan*/  check_Null (int /*<<< orphan*/ ,struct cert_status*,int,TYPE_2__ const*) ; 
 int decode_ExtKeyUsage (int /*<<< orphan*/ ,size_t,TYPE_3__*,size_t*) ; 
 int der_print_heim_oid (int /*<<< orphan*/ *,char,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_ExtKeyUsage (TYPE_3__*) ; 
 int /*<<< orphan*/  validate_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
check_extKeyUsage(hx509_validate_ctx ctx,
		  struct cert_status *status,
		  enum critical_flag cf,
		  const Extension *e)
{
    ExtKeyUsage eku;
    size_t size, i;
    int ret;

    check_Null(ctx, status, cf, e);

    ret = decode_ExtKeyUsage(e->extnValue.data,
			     e->extnValue.length,
			     &eku, &size);
    if (ret) {
	validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
		       "Decoding ExtKeyUsage failed: %d", ret);
	return 1;
    }
    if (size != e->extnValue.length) {
	validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
		       "Padding data in EKU");
	free_ExtKeyUsage(&eku);
	return 1;
    }
    if (eku.len == 0) {
	validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
		       "ExtKeyUsage length is 0");
	return 1;
    }

    for (i = 0; i < eku.len; i++) {
	char *str;
	ret = der_print_heim_oid (&eku.val[i], '.', &str);
	if (ret) {
	    validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
			   "\tEKU: failed to print oid %d", i);
	    free_ExtKeyUsage(&eku);
	    return 1;
	}
	validate_print(ctx, HX509_VALIDATE_F_VERBOSE,
		       "\teku-%d: %s\n", i, str);;
	free(str);
    }

    free_ExtKeyUsage(&eku);

    return 0;
}