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
struct eventtimer {int (* et_stop ) (struct eventtimer*) ;int /*<<< orphan*/  et_active; } ;

/* Variables and functions */
 int ENXIO ; 
 int stub1 (struct eventtimer*) ; 

int
et_stop(struct eventtimer *et)
{

	if (!et->et_active)
		return (ENXIO);
	if (et->et_stop)
		return (et->et_stop(et));
	return (0);
}