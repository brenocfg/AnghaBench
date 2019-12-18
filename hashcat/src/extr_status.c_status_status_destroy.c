#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int accessible; } ;
typedef  TYPE_1__ status_ctx_t ;
struct TYPE_8__ {int device_info_cnt; TYPE_4__* device_info_buf; int /*<<< orphan*/ * cpt; int /*<<< orphan*/ * guess_charset; int /*<<< orphan*/ * guess_mod; int /*<<< orphan*/ * guess_base; int /*<<< orphan*/ * speed_sec_all; int /*<<< orphan*/ * time_started_relative; int /*<<< orphan*/ * time_started_absolute; int /*<<< orphan*/ * time_estimated_relative; int /*<<< orphan*/ * time_estimated_absolute; int /*<<< orphan*/ * session; int /*<<< orphan*/ * hash_name; int /*<<< orphan*/ * hash_target; } ;
typedef  TYPE_2__ hashcat_status_t ;
struct TYPE_9__ {TYPE_1__* status_ctx; } ;
typedef  TYPE_3__ hashcat_ctx_t ;
struct TYPE_10__ {int /*<<< orphan*/ * brain_link_send_bytes_sec_dev; int /*<<< orphan*/ * brain_link_recv_bytes_sec_dev; int /*<<< orphan*/ * brain_link_send_bytes_dev; int /*<<< orphan*/ * brain_link_recv_bytes_dev; int /*<<< orphan*/ * hwmon_dev; int /*<<< orphan*/ * guess_candidates_dev; int /*<<< orphan*/ * speed_sec_dev; } ;
typedef  TYPE_4__ device_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  hcfree (int /*<<< orphan*/ *) ; 

void status_status_destroy (hashcat_ctx_t *hashcat_ctx, hashcat_status_t *hashcat_status)
{
  const status_ctx_t *status_ctx = hashcat_ctx->status_ctx;

  if (status_ctx == NULL) return;

  if (status_ctx->accessible == false) return;

  hcfree (hashcat_status->hash_target);
  hcfree (hashcat_status->hash_name);
  hcfree (hashcat_status->session);
  hcfree (hashcat_status->time_estimated_absolute);
  hcfree (hashcat_status->time_estimated_relative);
  hcfree (hashcat_status->time_started_absolute);
  hcfree (hashcat_status->time_started_relative);
  hcfree (hashcat_status->speed_sec_all);
  hcfree (hashcat_status->guess_base);
  hcfree (hashcat_status->guess_mod);
  hcfree (hashcat_status->guess_charset);
  hcfree (hashcat_status->cpt);

  hashcat_status->hash_target             = NULL;
  hashcat_status->hash_name               = NULL;
  hashcat_status->session                 = NULL;
  hashcat_status->time_estimated_absolute = NULL;
  hashcat_status->time_estimated_relative = NULL;
  hashcat_status->time_started_absolute   = NULL;
  hashcat_status->time_started_relative   = NULL;
  hashcat_status->speed_sec_all           = NULL;
  hashcat_status->guess_base              = NULL;
  hashcat_status->guess_mod               = NULL;
  hashcat_status->guess_charset           = NULL;
  hashcat_status->cpt                     = NULL;

  for (int device_id = 0; device_id < hashcat_status->device_info_cnt; device_id++)
  {
    device_info_t *device_info = hashcat_status->device_info_buf + device_id;

    hcfree (device_info->speed_sec_dev);
    hcfree (device_info->guess_candidates_dev);
    hcfree (device_info->hwmon_dev);
    #ifdef WITH_BRAIN
    hcfree (device_info->brain_link_recv_bytes_dev);
    hcfree (device_info->brain_link_send_bytes_dev);
    hcfree (device_info->brain_link_recv_bytes_sec_dev);
    hcfree (device_info->brain_link_send_bytes_sec_dev);
    #endif

    device_info->speed_sec_dev                  = NULL;
    device_info->guess_candidates_dev           = NULL;
    device_info->hwmon_dev                      = NULL;
    #ifdef WITH_BRAIN
    device_info->brain_link_recv_bytes_dev      = NULL;
    device_info->brain_link_send_bytes_dev      = NULL;
    device_info->brain_link_recv_bytes_sec_dev  = NULL;
    device_info->brain_link_send_bytes_sec_dev  = NULL;
    #endif
  }
}