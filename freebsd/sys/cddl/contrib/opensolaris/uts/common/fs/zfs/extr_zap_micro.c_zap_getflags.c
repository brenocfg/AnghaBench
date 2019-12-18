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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ zap_ismicro; } ;
typedef  TYPE_1__ zap_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  zap_flags; } ;

/* Variables and functions */
 TYPE_3__* zap_f_phys (TYPE_1__*) ; 

uint64_t
zap_getflags(zap_t *zap)
{
	if (zap->zap_ismicro)
		return (0);
	return (zap_f_phys(zap)->zap_flags);
}