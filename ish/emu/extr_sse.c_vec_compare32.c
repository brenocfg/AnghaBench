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

/* Variables and functions */
 scalar_t__ isnan (float) ; 
 int /*<<< orphan*/  printf (char*) ; 

void vec_compare32(struct cpu_state *cpu, float *f2, float *f1) {
    if (isnan(*f1) || isnan(*f2)) {
        cpu->zf = 1;
        cpu->pf = 1;
        cpu->cf = 1;
    }
    else if (*f1 > *f2) {
        cpu->zf = 0;
        cpu->pf = 0;
        cpu->cf = 0;
    }
    else if (*f1 < *f2) {
        cpu->zf = 0;
        cpu->pf = 0;
        cpu->cf = 1;
    }
    else if (*f1 == *f2) {
        cpu->zf = 1;
        cpu->pf = 0;
        cpu->cf = 0;
    }
    else {
        printf("something's horribly wrong. err 1093281094");
    }
    cpu->zf_res = 0;
    cpu->pf_res = 0;
}