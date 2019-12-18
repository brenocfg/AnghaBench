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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/ * v; } ;
typedef  TYPE_1__ block ;

/* Variables and functions */
 unsigned int ARGON2_QWORDS_IN_BLOCK ; 
 int /*<<< orphan*/  LOAD64_LE (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
load_block(block *dst, const void *input)
{
    unsigned i;
    for (i = 0; i < ARGON2_QWORDS_IN_BLOCK; ++i) {
        dst->v[i] = LOAD64_LE((const uint8_t *) input + i * sizeof(dst->v[i]));
    }
}