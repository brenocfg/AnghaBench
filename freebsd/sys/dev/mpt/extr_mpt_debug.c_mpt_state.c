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
typedef  int /*<<< orphan*/  u_int32_t ;

/* Variables and functions */
#define  MPT_DB_STATE_FAULT 131 
#define  MPT_DB_STATE_READY 130 
#define  MPT_DB_STATE_RESET 129 
#define  MPT_DB_STATE_RUNNING 128 
 int MPT_STATE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
mpt_state(u_int32_t mb)
{
	const char *text;

	switch (MPT_STATE(mb)) {
		case MPT_DB_STATE_RESET:  text = "Reset";   break;
		case MPT_DB_STATE_READY:  text = "Ready";   break;
		case MPT_DB_STATE_RUNNING:text = "Running"; break;
		case MPT_DB_STATE_FAULT:  text = "Fault";   break;
		default: 		  text = "Unknown"; break;
	}
	return text;
}