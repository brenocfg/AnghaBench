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
typedef  int /*<<< orphan*/  u_int32_t ;
struct sc_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENVY24_CCI_GPIODAT ; 
 int /*<<< orphan*/  envy24_rdci (struct sc_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
envy24_gpiord(struct sc_info *sc)
{
	return envy24_rdci(sc, ENVY24_CCI_GPIODAT);
}