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
typedef  int /*<<< orphan*/  au_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUE_AUDITON ; 
 int /*<<< orphan*/  AUE_AUDITON_GETCAR ; 
 int /*<<< orphan*/  AUE_AUDITON_GETCLASS ; 
 int /*<<< orphan*/  AUE_AUDITON_GETCOND ; 
 int /*<<< orphan*/  AUE_AUDITON_GETCWD ; 
 int /*<<< orphan*/  AUE_AUDITON_GETKMASK ; 
 int /*<<< orphan*/  AUE_AUDITON_GETSTAT ; 
 int /*<<< orphan*/  AUE_AUDITON_GPOLICY ; 
 int /*<<< orphan*/  AUE_AUDITON_GQCTRL ; 
 int /*<<< orphan*/  AUE_AUDITON_SETCLASS ; 
 int /*<<< orphan*/  AUE_AUDITON_SETCOND ; 
 int /*<<< orphan*/  AUE_AUDITON_SETKMASK ; 
 int /*<<< orphan*/  AUE_AUDITON_SETSMASK ; 
 int /*<<< orphan*/  AUE_AUDITON_SETSTAT ; 
 int /*<<< orphan*/  AUE_AUDITON_SETUMASK ; 
 int /*<<< orphan*/  AUE_AUDITON_SPOLICY ; 
 int /*<<< orphan*/  AUE_AUDITON_SQCTRL ; 
#define  A_GETCAR 150 
#define  A_GETCLASS 149 
#define  A_GETCOND 148 
#define  A_GETCWD 147 
#define  A_GETFSIZE 146 
#define  A_GETKAUDIT 145 
#define  A_GETKMASK 144 
#define  A_GETPINFO 143 
#define  A_GETPINFO_ADDR 142 
#define  A_GETPOLICY 141 
#define  A_GETQCTRL 140 
#define  A_GETSTAT 139 
#define  A_SETCLASS 138 
#define  A_SETCOND 137 
#define  A_SETFSIZE 136 
#define  A_SETKAUDIT 135 
#define  A_SETKMASK 134 
#define  A_SETPMASK 133 
#define  A_SETPOLICY 132 
#define  A_SETQCTRL 131 
#define  A_SETSMASK 130 
#define  A_SETSTAT 129 
#define  A_SETUMASK 128 

au_event_t
auditon_command_event(int cmd)
{

	switch(cmd) {
	case A_GETPOLICY:
		return (AUE_AUDITON_GPOLICY);

	case A_SETPOLICY:
		return (AUE_AUDITON_SPOLICY);

	case A_GETKMASK:
		return (AUE_AUDITON_GETKMASK);

	case A_SETKMASK:
		return (AUE_AUDITON_SETKMASK);

	case A_GETQCTRL:
		return (AUE_AUDITON_GQCTRL);

	case A_SETQCTRL:
		return (AUE_AUDITON_SQCTRL);

	case A_GETCWD:
		return (AUE_AUDITON_GETCWD);

	case A_GETCAR:
		return (AUE_AUDITON_GETCAR);

	case A_GETSTAT:
		return (AUE_AUDITON_GETSTAT);

	case A_SETSTAT:
		return (AUE_AUDITON_SETSTAT);

	case A_SETUMASK:
		return (AUE_AUDITON_SETUMASK);

	case A_SETSMASK:
		return (AUE_AUDITON_SETSMASK);

	case A_GETCOND:
		return (AUE_AUDITON_GETCOND);

	case A_SETCOND:
		return (AUE_AUDITON_SETCOND);

	case A_GETCLASS:
		return (AUE_AUDITON_GETCLASS);

	case A_SETCLASS:
		return (AUE_AUDITON_SETCLASS);

	case A_GETPINFO:
	case A_SETPMASK:
	case A_SETFSIZE:
	case A_GETFSIZE:
	case A_GETPINFO_ADDR:
	case A_GETKAUDIT:
	case A_SETKAUDIT:
	default:
		return (AUE_AUDITON);	/* No special record */
	}
}