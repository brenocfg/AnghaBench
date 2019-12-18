#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  normalized; int /*<<< orphan*/  magnitude; } ;
typedef  TYPE_1__ secp256k1_fe ;

/* Variables and functions */
 int memcmp (TYPE_1__ const*,TYPE_1__*,int) ; 

int fe_memcmp(const secp256k1_fe *a, const secp256k1_fe *b) {
    secp256k1_fe t = *b;
#ifdef VERIFY
    t.magnitude = a->magnitude;
    t.normalized = a->normalized;
#endif
    return memcmp(a, &t, sizeof(secp256k1_fe));
}