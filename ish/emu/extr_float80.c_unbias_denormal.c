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

/* Variables and functions */
 unsigned int EXP_DENORMAL ; 
 unsigned int EXP_MIN ; 
 int unbias (unsigned int) ; 

__attribute__((used)) static int unbias_denormal(unsigned exp) {
    if (exp == EXP_DENORMAL)
        return unbias(EXP_MIN);
    return unbias(exp);
}