#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  status_ctx_t ;
typedef  int /*<<< orphan*/  operation ;
struct TYPE_4__ {scalar_t__ pws_cnt; int brain_link_client_fd; } ;
typedef  TYPE_1__ hc_device_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  BRAIN_OPERATION_COMMIT ; 
 int /*<<< orphan*/  SEND_FLAGS ; 
 int brain_send (int const,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/  const*) ; 

bool brain_client_commit (hc_device_param_t *device_param, const status_ctx_t *status_ctx)
{
  if (device_param->pws_cnt == 0) return true;

  const int brain_link_client_fd = device_param->brain_link_client_fd;

  if (brain_link_client_fd == -1) return false;

  u8 operation = BRAIN_OPERATION_COMMIT;

  if (brain_send (brain_link_client_fd, &operation, sizeof (operation), SEND_FLAGS, device_param, status_ctx) == false) return false;

  return true;
}