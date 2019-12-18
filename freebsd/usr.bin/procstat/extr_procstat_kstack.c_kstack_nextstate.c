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
typedef  enum trace_state { ____Placeholder_trace_state } trace_state ;

/* Variables and functions */
#define  TS_AT 132 
#define  TS_FRAMENUM 131 
#define  TS_FUNC 130 
#define  TS_OFF 129 
#define  TS_PC 128 
 int /*<<< orphan*/  errx (int,char*) ; 

__attribute__((used)) static enum trace_state
kstack_nextstate(enum trace_state ts)
{

	switch (ts) {
	case TS_FRAMENUM:
		return (TS_PC);

	case TS_PC:
		return (TS_AT);

	case TS_AT:
		return (TS_FUNC);

	case TS_FUNC:
		return (TS_OFF);

	case TS_OFF:
		return TS_FRAMENUM;

	default:
		errx(-1, "kstack_nextstate");
	}
}