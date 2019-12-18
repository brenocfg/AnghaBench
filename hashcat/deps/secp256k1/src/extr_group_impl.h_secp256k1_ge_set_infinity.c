#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int infinity; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ secp256k1_ge ;

/* Variables and functions */
 int /*<<< orphan*/  secp256k1_fe_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void secp256k1_ge_set_infinity(secp256k1_ge *r) {
    r->infinity = 1;
    secp256k1_fe_clear(&r->x);
    secp256k1_fe_clear(&r->y);
}