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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct bintime {int frac; scalar_t__ sec; } ;
typedef  int UINT64 ;

/* Variables and functions */
 int /*<<< orphan*/  binuptime (struct bintime*) ; 

UINT64
AcpiOsGetTimer(void)
{
    struct bintime bt;
    UINT64 t;

    binuptime(&bt);
    t = (uint64_t)bt.sec * 10000000;
    t += ((uint64_t)10000000 * (uint32_t)(bt.frac >> 32)) >> 32;

    return (t);
}