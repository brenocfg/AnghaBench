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
 int base ; 
 unsigned int damp ; 
 unsigned int skew ; 
 int t_max ; 
 int t_min ; 

__attribute__((used)) static unsigned
adapt(unsigned delta, unsigned numpoints, int first)
{
    unsigned k;

    if (first)
	delta = delta / damp;
    else
	delta /= 2;
    delta += delta / numpoints;
    k = 0;
    while (delta > ((base - t_min) * t_max) / 2) {
	delta /= base - t_min;
	k += base;
    }
    return k + (((base - t_min + 1) * delta) / (delta + skew));
}