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
typedef  int /*<<< orphan*/  float64 ;

/* Variables and functions */
 int /*<<< orphan*/  ST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f80_to_double (int /*<<< orphan*/ ) ; 

void fpu_stm64(struct cpu_state *cpu, float64 *f) {
    *f = f80_to_double(ST(0));
}