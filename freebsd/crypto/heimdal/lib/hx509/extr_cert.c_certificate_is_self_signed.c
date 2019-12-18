#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_4__ {int /*<<< orphan*/  issuer; int /*<<< orphan*/  subject; } ;
struct TYPE_5__ {int /*<<< orphan*/  signatureAlgorithm; TYPE_1__ tbsCertificate; } ;
typedef  TYPE_2__ Certificate ;

/* Variables and functions */
 int _hx509_name_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int _hx509_self_signed_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int
certificate_is_self_signed(hx509_context context,
			   const Certificate *cert,
			   int *self_signed)
{
    int ret, diff;
    ret = _hx509_name_cmp(&cert->tbsCertificate.subject,
			  &cert->tbsCertificate.issuer, &diff);
    *self_signed = (diff == 0);
    if (ret) {
	hx509_set_error_string(context, 0, ret,
			       "Failed to check if self signed");
    } else
	ret = _hx509_self_signed_valid(context, &cert->signatureAlgorithm);

    return ret;
}