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
typedef  int int32_t ;
typedef  scalar_t__ VCHI_SERVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ SHIM_SERVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  vchiq_get_peer_version (int /*<<< orphan*/ ,short*) ; 
 int vchiq_status_to_vchi (int /*<<< orphan*/ ) ; 

int32_t vchi_get_peer_version( const VCHI_SERVICE_HANDLE_T handle, short *peer_version )
{
   int32_t ret = -1;
   SHIM_SERVICE_T *service = (SHIM_SERVICE_T *)handle;
   if(service)
   {
      VCHIQ_STATUS_T status = vchiq_get_peer_version(service->handle, peer_version);
      ret = vchiq_status_to_vchi( status );
   }
   return ret;
}