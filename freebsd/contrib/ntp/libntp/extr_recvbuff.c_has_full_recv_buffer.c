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
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/ * HEAD_FIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int /*<<< orphan*/  full_recv_fifo ; 

isc_boolean_t has_full_recv_buffer(void)
{
	if (HEAD_FIFO(full_recv_fifo) != NULL)
		return (ISC_TRUE);
	else
		return (ISC_FALSE);
}