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
struct TYPE_4__ {int /*<<< orphan*/  T2d; int /*<<< orphan*/  Z; int /*<<< orphan*/  YminusX; int /*<<< orphan*/  YplusX; } ;
typedef  TYPE_1__ ge25519_cached ;

/* Variables and functions */
 int /*<<< orphan*/  fe25519_cmov (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void
ge25519_cmov_cached(ge25519_cached *t, const ge25519_cached *u, unsigned char b)
{
    fe25519_cmov(t->YplusX, u->YplusX, b);
    fe25519_cmov(t->YminusX, u->YminusX, b);
    fe25519_cmov(t->Z, u->Z, b);
    fe25519_cmov(t->T2d, u->T2d, b);
}