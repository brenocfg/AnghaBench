#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ ** services; } ;
typedef  TYPE_1__ VCHIQ_STATE_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_T ;
typedef  int VCHIQ_SERVICE_HANDLE_T ;

/* Variables and functions */
 int VCHIQ_MAX_SERVICES ; 
 int VCHIQ_MAX_STATES ; 
 TYPE_1__** vchiq_states ; 

__attribute__((used)) static inline VCHIQ_SERVICE_T *
handle_to_service(VCHIQ_SERVICE_HANDLE_T handle)
{
	VCHIQ_STATE_T *state = vchiq_states[(handle / VCHIQ_MAX_SERVICES) &
		(VCHIQ_MAX_STATES - 1)];
	if (!state)
		return NULL;

	return state->services[handle & (VCHIQ_MAX_SERVICES - 1)];
}