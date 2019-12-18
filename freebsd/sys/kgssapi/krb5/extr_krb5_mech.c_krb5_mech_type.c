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
typedef  int /*<<< orphan*/  gss_ctx_id_t ;
typedef  int /*<<< orphan*/ * gss_OID ;

/* Variables and functions */
 int /*<<< orphan*/  krb5_mech_oid ; 

__attribute__((used)) static gss_OID
krb5_mech_type(gss_ctx_id_t ctx)
{

	return (&krb5_mech_oid);
}