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
struct session_state {int sign_object; int verify_object; void* verify_mechanism; void* sign_mechanism; } ;

/* Variables and functions */
 void* NULL_PTR ; 
 int /*<<< orphan*/  free (void*) ; 

__attribute__((used)) static void
reset_crypto_state(struct session_state *state)
{
    state->sign_object = -1;
    if (state->sign_mechanism)
	free(state->sign_mechanism);
    state->sign_mechanism = NULL_PTR;
    state->verify_object = -1;
    if (state->verify_mechanism)
	free(state->verify_mechanism);
    state->verify_mechanism = NULL_PTR;
}