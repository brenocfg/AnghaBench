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
typedef  size_t u_int ;
struct initiator_state {int dummy; } ;

/* Variables and functions */
 size_t MAX_INITIATORS ; 
 struct initiator_state* istates ; 
 int /*<<< orphan*/  warnx (char*,size_t,size_t) ; 

__attribute__((used)) static struct initiator_state *
tcmd_get_istate(u_int init_id)
{
	if (init_id >= MAX_INITIATORS) {
		warnx("illegal init_id %d, max %d", init_id, MAX_INITIATORS - 1);
		return (NULL);
	} else {
		return (&istates[init_id]);
	}
}