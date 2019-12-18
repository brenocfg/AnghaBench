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
struct caam_hash_state {int buflen_0; int buflen_1; scalar_t__ current_buf; } ;

/* Variables and functions */

__attribute__((used)) static inline int *alt_buflen(struct caam_hash_state *state)
{
	return state->current_buf ? &state->buflen_0 : &state->buflen_1;
}