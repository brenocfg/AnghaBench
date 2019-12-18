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
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int _ti_chip ; 

__attribute__((used)) static __inline int ti_chip(void)
{
	KASSERT(_ti_chip != -1, ("Can't determine TI Chip"));
	return _ti_chip;
}