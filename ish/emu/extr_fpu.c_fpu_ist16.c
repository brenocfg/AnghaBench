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
struct cpu_state {int dummy; } ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ST (int /*<<< orphan*/ ) ; 
 scalar_t__ f80_to_int (int /*<<< orphan*/ ) ; 

void fpu_ist16(struct cpu_state *cpu, int16_t *i) {
    *i = (int16_t) f80_to_int(ST(0));
}