#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int run_thread_level1; } ;
typedef  TYPE_1__ status_ctx_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_7__ {size_t pos; scalar_t__* bytes; int /*<<< orphan*/ * timer; } ;
typedef  TYPE_2__ link_speed_t ;
struct TYPE_8__ {int brain_link_recv_active; int /*<<< orphan*/  brain_link_recv_bytes; TYPE_2__ brain_link_recv_speed; } ;
typedef  TYPE_3__ hc_device_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_SPEED_COUNT ; 
 int /*<<< orphan*/  hc_timer_set (int /*<<< orphan*/ *) ; 
 scalar_t__ recv (int,char*,size_t,int) ; 

bool brain_recv_all (int sockfd, void *buf, size_t len, int flags, hc_device_param_t *device_param, const status_ctx_t *status_ctx)
{
  link_speed_t *link_speed = &device_param->brain_link_recv_speed;

  if (device_param)
  {
    device_param->brain_link_recv_active = true;

    hc_timer_set (&link_speed->timer[link_speed->pos]);
  }

  ssize_t nrecv = recv (sockfd, buf, len, flags);

  if (device_param)
  {
    link_speed->bytes[link_speed->pos] = nrecv;

    if (link_speed->pos++ == LINK_SPEED_COUNT) link_speed->pos = 0;

    device_param->brain_link_recv_bytes += nrecv;
  }

  if (nrecv <= 0) return false;

  if (status_ctx && status_ctx->run_thread_level1 == false) return false;

  while (nrecv < (ssize_t) len)
  {
    char *buf_new = (char *) buf;

    if (device_param)
    {
      hc_timer_set (&link_speed->timer[link_speed->pos]);
    }

    ssize_t nrecv_new = recv (sockfd, buf_new + nrecv, len - nrecv, flags);

    if (device_param)
    {
      link_speed->bytes[link_speed->pos] = nrecv_new;

      if (link_speed->pos++ == LINK_SPEED_COUNT) link_speed->pos = 0;

      device_param->brain_link_recv_bytes += nrecv_new;
    }

    if (nrecv_new <= 0) return false;

    if (status_ctx && status_ctx->run_thread_level1 == false) break;

    nrecv += nrecv_new;
  }

  if (device_param)
  {
    device_param->brain_link_recv_active = false;
  }

  return true;
}