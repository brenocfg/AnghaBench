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
struct jit_block {int dummy; } ;
struct jit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct jit_block*) ; 
 int /*<<< orphan*/  jit_block_disconnect (struct jit*,struct jit_block*) ; 

__attribute__((used)) static void jit_block_free(struct jit *jit, struct jit_block *block) {
    jit_block_disconnect(jit, block);
    free(block);
}