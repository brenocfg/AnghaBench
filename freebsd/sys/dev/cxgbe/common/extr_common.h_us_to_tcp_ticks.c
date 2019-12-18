#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int u_int ;
struct TYPE_5__ {int tre; } ;
struct TYPE_4__ {int cclk; } ;
struct TYPE_6__ {TYPE_2__ tp; TYPE_1__ vpd; } ;
struct adapter {TYPE_3__ params; } ;

/* Variables and functions */

__attribute__((used)) static inline u_int us_to_tcp_ticks(const struct adapter *adap, u_long us)
{

	return (us * adap->params.vpd.cclk / 1000 >> adap->params.tp.tre);
}