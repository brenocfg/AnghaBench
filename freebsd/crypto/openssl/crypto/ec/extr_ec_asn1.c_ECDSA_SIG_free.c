#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  s; int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ ECDSA_SIG ;

/* Variables and functions */
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

void ECDSA_SIG_free(ECDSA_SIG *sig)
{
    if (sig == NULL)
        return;
    BN_clear_free(sig->r);
    BN_clear_free(sig->s);
    OPENSSL_free(sig);
}