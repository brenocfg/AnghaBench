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
 int /*<<< orphan*/  SECP256K1_CONTEXT_VERIFY ; 
 int /*<<< orphan*/  secp256k1_context_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secp256k1_context_destroy (int /*<<< orphan*/ ) ; 

void bench_context_verify(void* arg) {
    int i;
    (void)arg;
    for (i = 0; i < 20; i++) {
        secp256k1_context_destroy(secp256k1_context_create(SECP256K1_CONTEXT_VERIFY));
    }
}