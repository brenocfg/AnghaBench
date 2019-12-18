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
struct TYPE_3__ {char const* name; void* opaque; int /*<<< orphan*/ * comp; int /*<<< orphan*/  rank; } ;
typedef  TYPE_1__ witness_t ;
typedef  int /*<<< orphan*/  witness_rank_t ;
typedef  int /*<<< orphan*/  witness_comp_t ;

/* Variables and functions */

void
witness_init(witness_t *witness, const char *name, witness_rank_t rank,
    witness_comp_t *comp, void *opaque) {
	witness->name = name;
	witness->rank = rank;
	witness->comp = comp;
	witness->opaque = opaque;
}