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
struct cpu_state {int zf; int pf; int cf; scalar_t__ pf_res; scalar_t__ zf_res; } ;
typedef  int /*<<< orphan*/  float80 ;

/* Variables and functions */
 int /*<<< orphan*/  ST (int /*<<< orphan*/ ) ; 
 int f80_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int f80_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ f80_uncomparable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fpu_comparei(struct cpu_state *cpu, float80 x) {
    cpu->zf_res = cpu->pf_res = 0;
    cpu->zf = cpu->pf = cpu->cf = 0;
    cpu->cf = f80_lt(ST(0), x);
    cpu->zf = f80_eq(ST(0), x);
    if (f80_uncomparable(ST(0), x))
        cpu->zf = cpu->pf = cpu->cf = 1;
}