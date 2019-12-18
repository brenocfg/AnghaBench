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
struct snprintf_state {int /*<<< orphan*/  (* append_char ) (struct snprintf_state*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int minus_flag ; 
 scalar_t__ pad (struct snprintf_state*,int,char) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (struct snprintf_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct snprintf_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
append_string (struct snprintf_state *state,
	       const unsigned char *arg,
	       int width,
	       int prec,
	       int flags)
{
    size_t len = 0;

    if(arg == NULL)
	arg = (const unsigned char*)"(null)";

    if(prec != -1)
	width -= prec;
    else
	width -= strlen((const char *)arg);
    if(!(flags & minus_flag))
	len += pad(state, width, ' ');

    if (prec != -1) {
	while (*arg && prec--) {
	    (*state->append_char) (state, *arg++);
	    ++len;
	}
    } else {
	while (*arg) {
	    (*state->append_char) (state, *arg++);
	    ++len;
	}
    }
    if(flags & minus_flag)
	len += pad(state, width, ' ');
    return len;
}