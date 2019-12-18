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
typedef  int /*<<< orphan*/  uuid_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  uuid_s_ok ; 
 int /*<<< orphan*/  uuidgen (int /*<<< orphan*/ *,int) ; 

void
uuid_create(uuid_t *u, uint32_t *status)
{

	if (status)
		*status = uuid_s_ok;

	uuidgen(u, 1);
}