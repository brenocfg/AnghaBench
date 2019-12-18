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
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_ca_tbs ;

/* Variables and functions */
 int add_utf8_san (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  asn1_oid_id_pkinit_ms_san ; 

int
hx509_ca_tbs_add_san_ms_upn(hx509_context context,
			    hx509_ca_tbs tbs,
			    const char *principal)
{
    return add_utf8_san(context, tbs, &asn1_oid_id_pkinit_ms_san, principal);
}