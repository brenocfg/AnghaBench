#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void (* local_cleanup ) (void*) ;void* local_cleanup_payload; } ;

/* Variables and functions */
 TYPE_1__ _clar ; 

void cl_set_cleanup(void (*cleanup)(void *), void *opaque)
{
	_clar.local_cleanup = cleanup;
	_clar.local_cleanup_payload = opaque;
}