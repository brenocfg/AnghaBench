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
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 double RAND (int /*<<< orphan*/ *) ; 
 scalar_t__ UINT_MAX ; 
 double log (int) ; 

__attribute__((used)) static double RAND_exp(U32* seed, double mean)
{
    double const u = RAND(seed) / (double) UINT_MAX;
    return log(1-u) * (-mean);
}