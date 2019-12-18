#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* bktr_ptr_t ;
struct TYPE_6__ {int channel; } ;
struct TYPE_7__ {TYPE_1__ tuner; } ;

/* Variables and functions */
 int /*<<< orphan*/  TV_FREQUENCY ; 
 int frequency_lookup (TYPE_2__*,int) ; 
 scalar_t__ tv_freq (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

int
tv_channel( bktr_ptr_t bktr, int channel )
{
	int frequency;

	/* calculate the frequency according to tuner type */
	if ( (frequency = frequency_lookup( bktr, channel )) < 0 )
		return( -1 );

	/* set the new frequency */
	if ( tv_freq( bktr, frequency, TV_FREQUENCY ) < 0 )
		return( -1 );

	/* OK to update records */
	return( (bktr->tuner.channel = channel) );
}