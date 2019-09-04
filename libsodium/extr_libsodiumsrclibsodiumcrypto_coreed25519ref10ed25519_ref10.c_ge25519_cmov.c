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
struct TYPE_4__ {int /*<<< orphan*/  xy2d; int /*<<< orphan*/  yminusx; int /*<<< orphan*/  yplusx; } ;
typedef  TYPE_1__ ge25519_precomp ;

/* Variables and functions */
 int /*<<< orphan*/  fe25519_cmov (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void
ge25519_cmov(ge25519_precomp *t, const ge25519_precomp *u, unsigned char b)
{
    fe25519_cmov(t->yplusx, u->yplusx, b);
    fe25519_cmov(t->yminusx, u->yminusx, b);
    fe25519_cmov(t->xy2d, u->xy2d, b);
}