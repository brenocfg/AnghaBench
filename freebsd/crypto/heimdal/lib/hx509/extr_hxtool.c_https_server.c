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
struct cert_type_opt {int dummy; } ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_ca_tbs ;

/* Variables and functions */
 int /*<<< orphan*/  asn1_oid_id_pkix_kp_serverAuth ; 
 int hx509_ca_tbs_add_eku (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
https_server(hx509_context contextp, hx509_ca_tbs tbs, struct cert_type_opt *opt)
{
    return hx509_ca_tbs_add_eku(contextp, tbs, &asn1_oid_id_pkix_kp_serverAuth);
}