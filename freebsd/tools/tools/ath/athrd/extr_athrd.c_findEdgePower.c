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
typedef  scalar_t__ u_int ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  RD_EDGES_POWER ;

/* Variables and functions */
 int /*<<< orphan*/ * AH_NULL ; 
 int NUM_EDGES ; 
 scalar_t__* _ctl ; 
 int _numCtls ; 
 int /*<<< orphan*/ * _rdEdgesPower ; 

__attribute__((used)) static RD_EDGES_POWER*
findEdgePower(struct ath_hal *ah, u_int ctl)
{
	int i;

	for (i = 0; i < _numCtls; i++)
		if (_ctl[i] == ctl)
			return &_rdEdgesPower[i * NUM_EDGES];
	return AH_NULL;
}