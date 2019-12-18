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
typedef  int /*<<< orphan*/  XXH_errorcode ;
typedef  int /*<<< orphan*/  XXH64_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  XXH_OK ; 
 int /*<<< orphan*/  XXH_free (int /*<<< orphan*/ *) ; 

XXH_errorcode XXH64_freeState(XXH64_state_t* statePtr)
{
    XXH_free(statePtr);
    return XXH_OK;
}