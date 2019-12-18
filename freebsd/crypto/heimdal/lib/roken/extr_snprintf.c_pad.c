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
 int /*<<< orphan*/  stub1 (struct snprintf_state*,char) ; 

__attribute__((used)) static size_t
pad(struct snprintf_state *state, int width, char c)
{
    size_t len = 0;
    while(width-- > 0){
	(*state->append_char)(state,  c);
	++len;
    }
    return len;
}