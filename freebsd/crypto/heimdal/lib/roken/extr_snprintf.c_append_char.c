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
struct snprintf_state {int /*<<< orphan*/  (* append_char ) (struct snprintf_state*,char) ;} ;

/* Variables and functions */
 int minus_flag ; 
 int /*<<< orphan*/  stub1 (struct snprintf_state*,char) ; 
 int /*<<< orphan*/  stub2 (struct snprintf_state*,unsigned char) ; 
 int /*<<< orphan*/  stub3 (struct snprintf_state*,char) ; 

__attribute__((used)) static int
append_char(struct snprintf_state *state,
	    unsigned char arg,
	    int width,
	    int flags)
{
    int len = 0;

    while(!(flags & minus_flag) && --width > 0) {
	(*state->append_char) (state, ' ')    ;
	++len;
    }
    (*state->append_char) (state, arg);
    ++len;
    while((flags & minus_flag) && --width > 0) {
	(*state->append_char) (state, ' ');
	++len;
    }
    return 0;
}