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

/* Variables and functions */
 int /*<<< orphan*/  ibmp ; 
 void* mad_receive_via (void*,int,int /*<<< orphan*/ ) ; 

void *mad_receive(void *umad, int timeout)
{
	return mad_receive_via(umad, timeout, ibmp);
}