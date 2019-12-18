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
struct TYPE_3__ {int pad_boundary; } ;
struct TYPE_4__ {TYPE_1__ sge; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 scalar_t__ fl_pad ; 

__attribute__((used)) static inline int
hwsz_ok(struct adapter *sc, int hwsz)
{
	int mask = fl_pad ? sc->params.sge.pad_boundary - 1 : 16 - 1;

	return (hwsz >= 64 && (hwsz & mask) == 0);
}