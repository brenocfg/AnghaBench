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
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCHIQ_BULK_MODE_CALLBACK ; 
 int /*<<< orphan*/  VCHIQ_BULK_RECEIVE ; 
 int /*<<< orphan*/  VCHI_MEM_HANDLE_INVALID ; 
 int /*<<< orphan*/  vchiq_bulk_transfer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,unsigned int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VCHIQ_STATUS_T
vchiq_queue_bulk_receive(VCHIQ_SERVICE_HANDLE_T handle, void *data,
	unsigned int size, void *userdata)
{
	return vchiq_bulk_transfer(handle,
		VCHI_MEM_HANDLE_INVALID, data, size, userdata,
		VCHIQ_BULK_MODE_CALLBACK, VCHIQ_BULK_RECEIVE);
}