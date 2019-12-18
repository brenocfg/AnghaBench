#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cert_type_opt {int /*<<< orphan*/  pkinit; } ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_ca_tbs ;

/* Variables and functions */
 int /*<<< orphan*/  asn1_oid_id_ms_client_authentication ; 
 int /*<<< orphan*/  asn1_oid_id_pkekuoid ; 
 int /*<<< orphan*/  asn1_oid_id_pkinit_ms_eku ; 
 int /*<<< orphan*/  context ; 
 int hx509_ca_tbs_add_eku (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pkinit_client(hx509_context contextp, hx509_ca_tbs tbs, struct cert_type_opt *opt)
{
    int ret;

    opt->pkinit++;

    ret = hx509_ca_tbs_add_eku(contextp, tbs, &asn1_oid_id_pkekuoid);
    if (ret)
	return ret;

    ret = hx509_ca_tbs_add_eku(context, tbs, &asn1_oid_id_ms_client_authentication);
    if (ret)
	return ret;

    return hx509_ca_tbs_add_eku(context, tbs, &asn1_oid_id_pkinit_ms_eku);
}