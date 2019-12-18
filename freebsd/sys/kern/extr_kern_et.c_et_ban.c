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
struct eventtimer {int et_flags; } ;

/* Variables and functions */
 int ET_FLAGS_ONESHOT ; 
 int ET_FLAGS_PERIODIC ; 

int
et_ban(struct eventtimer *et)
{

	et->et_flags &= ~(ET_FLAGS_PERIODIC | ET_FLAGS_ONESHOT);
	return (0);
}