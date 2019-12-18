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
typedef  int /*<<< orphan*/  secp256k1_scalar ;
typedef  int /*<<< orphan*/  secp256k1_ge ;

/* Variables and functions */

__attribute__((used)) static int ecmult_multi_false_callback(secp256k1_scalar *sc, secp256k1_ge *pt, size_t idx, void *cbdata) {
    (void)sc;
    (void)pt;
    (void)idx;
    (void)cbdata;
    return 0;
}