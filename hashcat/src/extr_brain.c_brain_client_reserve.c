#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  work ;
typedef  int /*<<< orphan*/  words_off ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  status_ctx_t ;
typedef  int /*<<< orphan*/  operation ;
struct TYPE_5__ {int brain_link_client_fd; } ;
typedef  TYPE_1__ hc_device_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  BRAIN_OPERATION_ATTACK_RESERVE ; 
 int /*<<< orphan*/  SEND_FLAGS ; 
 int brain_recv (int const,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int brain_send (int const,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/  const*) ; 

bool brain_client_reserve (hc_device_param_t *device_param, const status_ctx_t *status_ctx, u64 words_off, u64 work, u64 *overlap)
{
  const int brain_link_client_fd = device_param->brain_link_client_fd;

  if (brain_link_client_fd == -1) return false;

  u8 operation = BRAIN_OPERATION_ATTACK_RESERVE;

  if (brain_send (brain_link_client_fd, &operation, sizeof (operation), SEND_FLAGS, device_param, status_ctx) == false) return false;
  if (brain_send (brain_link_client_fd, &words_off, sizeof (words_off),          0, device_param, status_ctx) == false) return false;
  if (brain_send (brain_link_client_fd, &work,           sizeof (work),          0, device_param, status_ctx) == false) return false;

  if (brain_recv (brain_link_client_fd, overlap,          sizeof (u64),          0, device_param, status_ctx) == false) return false;

  return true;
}