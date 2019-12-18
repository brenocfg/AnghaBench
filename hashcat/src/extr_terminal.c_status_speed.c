#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int machine_readable; int status_json; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_15__ {int device_info_cnt; int device_info_active; int /*<<< orphan*/  speed_sec_all; TYPE_4__* device_info_buf; } ;
typedef  TYPE_2__ hashcat_status_t ;
struct TYPE_16__ {TYPE_1__* user_options; } ;
typedef  TYPE_3__ hashcat_ctx_t ;
struct TYPE_17__ {int skipped_dev; int skipped_warning_dev; int /*<<< orphan*/  exec_msec_dev; int /*<<< orphan*/  speed_sec_dev; } ;
typedef  TYPE_4__ device_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  event_log_info (TYPE_3__*,char*,int,...) ; 
 int hashcat_get_status (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  hcfree (TYPE_2__*) ; 
 scalar_t__ hcmalloc (int) ; 
 int /*<<< orphan*/  status_speed_json (TYPE_3__*) ; 
 int /*<<< orphan*/  status_speed_machine_readable (TYPE_3__*) ; 
 int /*<<< orphan*/  status_status_destroy (TYPE_3__*,TYPE_2__*) ; 

void status_speed (hashcat_ctx_t *hashcat_ctx)
{
  const user_options_t *user_options = hashcat_ctx->user_options;

  if (user_options->machine_readable == true)
  {
    status_speed_machine_readable (hashcat_ctx);

    return;
  }

  if (user_options->status_json == true)
  {
    status_speed_json (hashcat_ctx);

    return;
  }

  hashcat_status_t *hashcat_status = (hashcat_status_t *) hcmalloc (sizeof (hashcat_status_t));

  if (hashcat_get_status (hashcat_ctx, hashcat_status) == -1)
  {
    hcfree (hashcat_status);

    return;
  }

  for (int device_id = 0; device_id < hashcat_status->device_info_cnt; device_id++)
  {
    const device_info_t *device_info = hashcat_status->device_info_buf + device_id;

    if (device_info->skipped_dev == true) continue;

    if (device_info->skipped_warning_dev == true) continue;

    event_log_info (hashcat_ctx,
      "Speed.#%d.........: %9sH/s (%0.2fms)", device_id + 1,
      device_info->speed_sec_dev,
      device_info->exec_msec_dev);
  }

  if (hashcat_status->device_info_active > 1)
  {
    event_log_info (hashcat_ctx,
      "Speed.#*.........: %9sH/s",
      hashcat_status->speed_sec_all);
  }

  status_status_destroy (hashcat_ctx, hashcat_status);

  hcfree (hashcat_status);
}