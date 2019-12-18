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
typedef  int uint8_t ;
struct vatpit {int dummy; } ;

/* Variables and functions */
 int TIMER_RB_CTR_0 ; 
 int TIMER_RB_CTR_1 ; 
 int TIMER_RB_CTR_2 ; 
 int pit_readback1 (struct vatpit*,int,int) ; 

__attribute__((used)) static int
pit_readback(struct vatpit *vatpit, uint8_t cmd)
{
	int error;

	/*
	 * The readback command can apply to all timers.
	 */
	error = 0;
	if (cmd & TIMER_RB_CTR_0)
		error = pit_readback1(vatpit, 0, cmd);
	if (!error && cmd & TIMER_RB_CTR_1)
		error = pit_readback1(vatpit, 1, cmd);
	if (!error && cmd & TIMER_RB_CTR_2)
		error = pit_readback1(vatpit, 2, cmd);

	return (error);
}