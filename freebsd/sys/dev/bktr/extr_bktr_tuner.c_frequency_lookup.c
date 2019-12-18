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
typedef  int /*<<< orphan*/  bktr_ptr_t ;

/* Variables and functions */
 int TBL_BASE_FREQ ; 
 int TBL_CHNL ; 
 int TBL_OFFSET ; 

__attribute__((used)) static int
frequency_lookup( bktr_ptr_t bktr, int channel )
{
	int	x;

	/* check for "> MAX channel" */
	x = 0;
	if ( channel > TBL_CHNL )
		return( -1 );

	/* search the table for data */
	for ( x = 3; TBL_CHNL; x += 3 ) {
		if ( channel >= TBL_CHNL ) {
			return( TBL_BASE_FREQ +
				 ((channel - TBL_CHNL) * TBL_OFFSET) );
		}
	}

	/* not found, must be below the MIN channel */
	return( -1 );
}