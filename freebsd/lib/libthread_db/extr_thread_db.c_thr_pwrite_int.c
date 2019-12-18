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
typedef  int /*<<< orphan*/  uint32_t ;
struct td_thragent {int /*<<< orphan*/  ph; } ;
typedef  int /*<<< orphan*/  psaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BYTE_ORDER ; 
 int thr_pwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
thr_pwrite_int(const struct td_thragent *ta, psaddr_t addr, uint32_t val)
{

	return (thr_pwrite(ta->ph, addr, val, sizeof(int), BYTE_ORDER));
}