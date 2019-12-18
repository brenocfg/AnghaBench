#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct cert_status {int dummy; } ;
typedef  int /*<<< orphan*/  hx509_validate_ctx ;
typedef  enum critical_flag { ____Placeholder_critical_flag } critical_flag ;
struct TYPE_12__ {size_t len; TYPE_2__* val; } ;
struct TYPE_9__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_1__ extnValue; } ;
struct TYPE_10__ {int /*<<< orphan*/  accessLocation; int /*<<< orphan*/  accessMethod; } ;
typedef  TYPE_3__ Extension ;
typedef  TYPE_4__ AuthorityInfoAccessSyntax ;

/* Variables and functions */
 int /*<<< orphan*/  HX509_VALIDATE_F_VERBOSE ; 
 int /*<<< orphan*/  check_Null (int /*<<< orphan*/ ,struct cert_status*,int,TYPE_3__ const*) ; 
 int decode_AuthorityInfoAccessSyntax (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,size_t*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_AuthorityInfoAccessSyntax (TYPE_4__*) ; 
 int /*<<< orphan*/  hx509_general_name_unparse (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  hx509_oid_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  validate_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  validate_vprint ; 

__attribute__((used)) static int
check_authorityInfoAccess(hx509_validate_ctx ctx,
			  struct cert_status *status,
			  enum critical_flag cf,
			  const Extension *e)
{
    AuthorityInfoAccessSyntax aia;
    size_t size;
    int ret;
    size_t i;

    check_Null(ctx, status, cf, e);

    ret = decode_AuthorityInfoAccessSyntax(e->extnValue.data,
					   e->extnValue.length,
					   &aia, &size);
    if (ret) {
	printf("\tret = %d while decoding AuthorityInfoAccessSyntax\n", ret);
	return 0;
    }

    for (i = 0; i < aia.len; i++) {
	char *str;
	validate_print(ctx, HX509_VALIDATE_F_VERBOSE,
		       "\ttype: ");
	hx509_oid_print(&aia.val[i].accessMethod, validate_vprint, ctx);
	hx509_general_name_unparse(&aia.val[i].accessLocation, &str);
	validate_print(ctx, HX509_VALIDATE_F_VERBOSE,
		       "\n\tdirname: %s\n", str);
	free(str);
    }
    free_AuthorityInfoAccessSyntax(&aia);

    return 0;
}