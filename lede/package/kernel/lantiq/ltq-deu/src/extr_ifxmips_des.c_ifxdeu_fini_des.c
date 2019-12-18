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

/* Variables and functions */
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifxdeu_cbc_des3_ede_alg ; 
 int /*<<< orphan*/  ifxdeu_cbc_des_alg ; 
 int /*<<< orphan*/  ifxdeu_des3_ede_alg ; 
 int /*<<< orphan*/  ifxdeu_des_alg ; 
 int /*<<< orphan*/  ifxdeu_ecb_des3_ede_alg ; 
 int /*<<< orphan*/  ifxdeu_ecb_des_alg ; 

void ifxdeu_fini_des (void)
{
        crypto_unregister_alg (&ifxdeu_des_alg);
        crypto_unregister_alg (&ifxdeu_ecb_des_alg);
        crypto_unregister_alg (&ifxdeu_cbc_des_alg);
        crypto_unregister_alg (&ifxdeu_des3_ede_alg);
        crypto_unregister_alg (&ifxdeu_ecb_des3_ede_alg);
        crypto_unregister_alg (&ifxdeu_cbc_des3_ede_alg);

}