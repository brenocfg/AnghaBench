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
typedef  char u8 ;
typedef  int /*<<< orphan*/  status_ctx_t ;
typedef  int /*<<< orphan*/  out_size ;
typedef  int /*<<< orphan*/  operation ;
typedef  int /*<<< orphan*/  in_size ;
struct TYPE_3__ {int pws_pre_cnt; int brain_link_client_fd; scalar_t__ size_brain_link_in; scalar_t__ brain_link_out_buf; scalar_t__ brain_link_in_buf; } ;
typedef  TYPE_1__ hc_device_param_t ;

/* Variables and functions */
 int BRAIN_HASH_SIZE ; 
 char BRAIN_OPERATION_HASH_LOOKUP ; 
 int /*<<< orphan*/  SEND_FLAGS ; 
 int brain_recv (int const,...) ; 
 int brain_send (int const,...) ; 

bool brain_client_lookup (hc_device_param_t *device_param, const status_ctx_t *status_ctx)
{
  if (device_param->pws_pre_cnt == 0) return true;

  const int brain_link_client_fd = device_param->brain_link_client_fd;

  if (brain_link_client_fd == -1) return false;

  char *recvbuf = (char *) device_param->brain_link_in_buf;
  char *sendbuf = (char *) device_param->brain_link_out_buf;

  int in_size  = 0;
  int out_size = device_param->pws_pre_cnt * BRAIN_HASH_SIZE;

  u8 operation = BRAIN_OPERATION_HASH_LOOKUP;

  if (brain_send (brain_link_client_fd, &operation, sizeof (operation), SEND_FLAGS, device_param, status_ctx) == false) return false;
  if (brain_send (brain_link_client_fd, &out_size,   sizeof (out_size), SEND_FLAGS, device_param, status_ctx) == false) return false;
  if (brain_send (brain_link_client_fd, sendbuf,              out_size, SEND_FLAGS, device_param, status_ctx) == false) return false;

  if (brain_recv (brain_link_client_fd, &in_size,     sizeof (in_size),          0, device_param, status_ctx) == false) return false;

  if (in_size > (int) device_param->size_brain_link_in) return false;

  if (brain_recv (brain_link_client_fd, recvbuf,      (size_t) in_size,          0, device_param, status_ctx) == false) return false;

  return true;
}