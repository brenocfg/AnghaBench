#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_8__ {int /*<<< orphan*/  serial; int /*<<< orphan*/  issuer; } ;
struct TYPE_6__ {int /*<<< orphan*/  dirn; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_1__ d; } ;
typedef  TYPE_2__ GENERAL_NAME ;
typedef  TYPE_3__ ESS_ISSUER_SERIAL ;

/* Variables and functions */
 scalar_t__ ASN1_INTEGER_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GEN_DIRNAME ; 
 scalar_t__ X509_NAME_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_get_issuer_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_serialNumber (int /*<<< orphan*/ *) ; 
 int sk_GENERAL_NAME_num (int /*<<< orphan*/ ) ; 
 TYPE_2__* sk_GENERAL_NAME_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ts_issuer_serial_cmp(ESS_ISSUER_SERIAL *is, X509 *cert)
{
    GENERAL_NAME *issuer;

    if (!is || !cert || sk_GENERAL_NAME_num(is->issuer) != 1)
        return -1;

    issuer = sk_GENERAL_NAME_value(is->issuer, 0);
    if (issuer->type != GEN_DIRNAME
        || X509_NAME_cmp(issuer->d.dirn, X509_get_issuer_name(cert)))
        return -1;

    if (ASN1_INTEGER_cmp(is->serial, X509_get_serialNumber(cert)))
        return -1;

    return 0;
}