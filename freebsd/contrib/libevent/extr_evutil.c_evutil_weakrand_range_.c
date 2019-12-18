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
struct evutil_weakrand_state {int dummy; } ;
typedef  int ev_int32_t ;

/* Variables and functions */
 int EVUTIL_WEAKRAND_MAX ; 
 int evutil_weakrand_ (struct evutil_weakrand_state*) ; 

ev_int32_t
evutil_weakrand_range_(struct evutil_weakrand_state *state, ev_int32_t top)
{
	ev_int32_t divisor, result;

	/* We can't just do weakrand() % top, since the low bits of the LCG
	 * are less random than the high ones.  (Specifically, since the LCG
	 * modulus is 2^N, every 2^m for m<N will divide the modulus, and so
	 * therefore the low m bits of the LCG will have period 2^m.) */
	divisor = EVUTIL_WEAKRAND_MAX / top;
	do {
		result = evutil_weakrand_(state) / divisor;
	} while (result >= top);
	return result;
}