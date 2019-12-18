#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_3__ {int cclk; } ;
struct TYPE_4__ {TYPE_1__ vpd; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 int UINT64_MAX ; 
 int be64toh (int) ; 

__attribute__((used)) static inline uint64_t
last_flit_to_ns(struct adapter *sc, uint64_t lf)
{
	uint64_t n = be64toh(lf) & 0xfffffffffffffff;	/* 60b, not 64b. */

	if (n > UINT64_MAX / 1000000)
		return (n / sc->params.vpd.cclk * 1000000);
	else
		return (n * 1000000 / sc->params.vpd.cclk);
}