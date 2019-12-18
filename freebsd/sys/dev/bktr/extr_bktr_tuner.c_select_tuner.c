#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* bktr_ptr_t ;
struct TYPE_4__ {int /*<<< orphan*/ * tuner; } ;
struct TYPE_5__ {TYPE_1__ card; } ;

/* Variables and functions */
 int Bt848_MAX_TUNER ; 
 int /*<<< orphan*/ * tuners ; 

void    select_tuner( bktr_ptr_t bktr, int tuner_type ) {
	if (tuner_type < Bt848_MAX_TUNER) {
		bktr->card.tuner = &tuners[ tuner_type ];
	} else {
		bktr->card.tuner = NULL;
	}
}