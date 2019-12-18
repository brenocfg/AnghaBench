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
#define  ED_IDLE 130 
#define  ED_OPER 129 
#define  ED_UNLINK 128 

__attribute__((used)) static inline char *ed_statestring(int state)
{
	switch (state) {
	case ED_IDLE:
		return "IDLE";
	case ED_UNLINK:
		return "UNLINK";
	case ED_OPER:
		return "OPER";
	}
	return "?STATE";
}