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
 int /*<<< orphan*/  current_time ; 
 scalar_t__ sys_badauth ; 
 scalar_t__ sys_badlength ; 
 scalar_t__ sys_declined ; 
 scalar_t__ sys_kodsent ; 
 scalar_t__ sys_lamport ; 
 scalar_t__ sys_limitrejected ; 
 scalar_t__ sys_newversion ; 
 scalar_t__ sys_oldversion ; 
 scalar_t__ sys_processed ; 
 scalar_t__ sys_received ; 
 scalar_t__ sys_restricted ; 
 int /*<<< orphan*/  sys_stattime ; 
 scalar_t__ sys_tsrounding ; 

void
proto_clr_stats(void)
{
	sys_stattime = current_time;
	sys_received = 0;
	sys_processed = 0;
	sys_newversion = 0;
	sys_oldversion = 0;
	sys_declined = 0;
	sys_restricted = 0;
	sys_badlength = 0;
	sys_badauth = 0;
	sys_limitrejected = 0;
	sys_kodsent = 0;
	sys_lamport = 0;
	sys_tsrounding = 0;
}