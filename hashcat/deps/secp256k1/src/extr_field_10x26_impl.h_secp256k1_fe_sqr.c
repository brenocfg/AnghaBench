#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int magnitude; scalar_t__ normalized; int /*<<< orphan*/  n; } ;
typedef  TYPE_1__ const secp256k1_fe ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY_CHECK (int) ; 
 int /*<<< orphan*/  secp256k1_fe_sqr_inner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secp256k1_fe_verify (TYPE_1__ const*) ; 

__attribute__((used)) static void secp256k1_fe_sqr(secp256k1_fe *r, const secp256k1_fe *a) {
#ifdef VERIFY
    VERIFY_CHECK(a->magnitude <= 8);
    secp256k1_fe_verify(a);
#endif
    secp256k1_fe_sqr_inner(r->n, a->n);
#ifdef VERIFY
    r->magnitude = 1;
    r->normalized = 0;
    secp256k1_fe_verify(r);
#endif
}