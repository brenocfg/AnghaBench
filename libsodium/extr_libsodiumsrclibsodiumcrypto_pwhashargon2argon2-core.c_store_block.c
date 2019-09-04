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
 int /*<<< orphan*/  STORE64_LE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
store_block(void *output, const block *src)
{
    unsigned i;
    for (i = 0; i < ARGON2_QWORDS_IN_BLOCK; ++i) {
        STORE64_LE((uint8_t *) output + i * sizeof(src->v[i]), src->v[i]);
    }
}