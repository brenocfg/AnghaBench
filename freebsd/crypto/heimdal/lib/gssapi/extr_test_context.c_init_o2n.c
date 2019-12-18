#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_KRB5_MECHANISM ; 
 int /*<<< orphan*/  GSS_NTLM_MECHANISM ; 
 int /*<<< orphan*/  GSS_SASL_DIGEST_MD5_MECHANISM ; 
 int /*<<< orphan*/  GSS_SPNEGO_MECHANISM ; 
 TYPE_1__* o2n ; 

__attribute__((used)) static void
init_o2n(void)
{
    o2n[0].oid = GSS_KRB5_MECHANISM;
    o2n[1].oid = GSS_SPNEGO_MECHANISM;
    o2n[2].oid = GSS_NTLM_MECHANISM;
    o2n[3].oid = GSS_SASL_DIGEST_MD5_MECHANISM;
}