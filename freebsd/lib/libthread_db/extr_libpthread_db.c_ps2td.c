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
#define  PS_BADADDR 134 
#define  PS_BADLID 133 
#define  PS_BADPID 132 
#define  PS_ERR 131 
#define  PS_NOFREGS 130 
#define  PS_NOSYM 129 
#define  PS_OK 128 
 int TD_BADPH ; 
 int TD_ERR ; 
 int TD_NOFPREGS ; 
 int TD_NOLIBTHREAD ; 
 int TD_NOLWP ; 
 int TD_OK ; 

__attribute__((used)) static int
ps2td(int c)
{
	switch (c) {
	case PS_OK:
		return TD_OK;
	case PS_ERR:
		return TD_ERR;
	case PS_BADPID:
		return TD_BADPH;
	case PS_BADLID:
		return TD_NOLWP;
	case PS_BADADDR:
		return TD_ERR;
	case PS_NOSYM:
		return TD_NOLIBTHREAD;
	case PS_NOFREGS:
		return TD_NOFPREGS;
	default:
		return TD_ERR;
	}
}