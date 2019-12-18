#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void** c_cc; } ;

/* Variables and functions */
 scalar_t__ CINTR ; 
 scalar_t__ CKILL ; 
 scalar_t__ DISABLED (void*) ; 
 void* UChar (scalar_t__) ; 
 size_t VERASE ; 
 size_t VINTR ; 
 size_t VKILL ; 
 scalar_t__ default_erase () ; 
 scalar_t__ intrchar ; 
 TYPE_1__ mode ; 
 scalar_t__ terasechar ; 
 scalar_t__ tkillchar ; 

__attribute__((used)) static void
set_control_chars(void)
{
#ifdef TERMIOS
    if (DISABLED(mode.c_cc[VERASE]) || terasechar >= 0) {
	mode.c_cc[VERASE] = UChar((terasechar >= 0)
				  ? terasechar
				  : default_erase());
    }

    if (DISABLED(mode.c_cc[VINTR]) || intrchar >= 0) {
	mode.c_cc[VINTR] = UChar((intrchar >= 0)
				 ? intrchar
				 : CINTR);
    }

    if (DISABLED(mode.c_cc[VKILL]) || tkillchar >= 0) {
	mode.c_cc[VKILL] = UChar((tkillchar >= 0)
				 ? tkillchar
				 : CKILL);
    }
#endif
}