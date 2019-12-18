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
typedef  size_t uint32_t ;

/* Variables and functions */
 size_t MAX_TYPES ; 
 size_t TYPE_0 ; 
 size_t* degrees ; 
 size_t* end_ptr ; 
 size_t* fptr ; 
 size_t rand_deg ; 
 size_t rand_sep ; 
 size_t rand_type ; 
 size_t* rptr ; 
 size_t* seps ; 
 size_t* state ; 

char *
setstate(char *arg_state)
{
	uint32_t *new_state = (uint32_t *)arg_state;
	uint32_t type = new_state[0] % MAX_TYPES;
	uint32_t rear = new_state[0] / MAX_TYPES;
	char *ostate = (char *)(&state[-1]);

	if (type != TYPE_0 && rear >= degrees[type])
		return (NULL);
	if (rand_type == TYPE_0)
		state[-1] = rand_type;
	else
		state[-1] = MAX_TYPES * (rptr - state) + rand_type;
	rand_type = type;
	rand_deg = degrees[type];
	rand_sep = seps[type];
	state = new_state + 1;
	if (rand_type != TYPE_0) {
		rptr = &state[rear];
		fptr = &state[(rear + rand_sep) % rand_deg];
	}
	end_ptr = &state[rand_deg];		/* set end_ptr too */
	return (ostate);
}