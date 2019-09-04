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
 int /*<<< orphan*/  S_CodecCloseStream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * s_backgroundStream ; 
 scalar_t__* s_rawend ; 

void S_Base_StopBackgroundTrack( void ) {
	if(!s_backgroundStream)
		return;
	S_CodecCloseStream(s_backgroundStream);
	s_backgroundStream = NULL;
	s_rawend[0] = 0;
}