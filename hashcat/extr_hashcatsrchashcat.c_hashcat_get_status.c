#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_91__   TYPE_84__ ;
typedef  struct TYPE_90__   TYPE_4__ ;
typedef  struct TYPE_89__   TYPE_3__ ;
typedef  struct TYPE_88__   TYPE_2__ ;
typedef  struct TYPE_87__   TYPE_1__ ;

/* Type definitions */
struct TYPE_87__ {int accessible; TYPE_84__* hashcat_status_final; } ;
typedef  TYPE_1__ status_ctx_t ;
struct TYPE_88__ {int device_info_cnt; int /*<<< orphan*/  speed_sec_all; int /*<<< orphan*/  exec_msec_all; int /*<<< orphan*/  hashes_msec_all; TYPE_4__* device_info_buf; int /*<<< orphan*/  device_info_active; int /*<<< orphan*/  cpt; int /*<<< orphan*/  cpt_avg_day; int /*<<< orphan*/  cpt_avg_hour; int /*<<< orphan*/  cpt_avg_min; int /*<<< orphan*/  cpt_cur_day; int /*<<< orphan*/  cpt_cur_hour; int /*<<< orphan*/  cpt_cur_min; int /*<<< orphan*/  time_started_relative; int /*<<< orphan*/  time_started_absolute; int /*<<< orphan*/  time_estimated_relative; int /*<<< orphan*/  time_estimated_absolute; int /*<<< orphan*/  status_number; int /*<<< orphan*/  status_string; int /*<<< orphan*/  session; int /*<<< orphan*/  salts_percent; int /*<<< orphan*/  salts_done; int /*<<< orphan*/  salts_cnt; int /*<<< orphan*/  restore_percent; int /*<<< orphan*/  restore_total; int /*<<< orphan*/  restore_point; int /*<<< orphan*/  progress_skip; int /*<<< orphan*/  progress_restored; int /*<<< orphan*/  progress_rejected_percent; int /*<<< orphan*/  progress_rejected; int /*<<< orphan*/  progress_ignore; int /*<<< orphan*/  progress_end; int /*<<< orphan*/  progress_end_relative_skip; int /*<<< orphan*/  progress_done; int /*<<< orphan*/  progress_cur; int /*<<< orphan*/  progress_cur_relative_skip; int /*<<< orphan*/  progress_finished_percent; int /*<<< orphan*/  progress_mode; int /*<<< orphan*/  msec_real; int /*<<< orphan*/  msec_running; int /*<<< orphan*/  msec_paused; int /*<<< orphan*/  guess_mode; int /*<<< orphan*/  guess_mask_length; int /*<<< orphan*/  guess_charset; int /*<<< orphan*/  guess_mod_percent; int /*<<< orphan*/  guess_mod_count; int /*<<< orphan*/  guess_mod_offset; int /*<<< orphan*/  guess_mod; int /*<<< orphan*/  guess_base_percent; int /*<<< orphan*/  guess_base_count; int /*<<< orphan*/  guess_base_offset; int /*<<< orphan*/  guess_base; int /*<<< orphan*/  hash_name; int /*<<< orphan*/  hash_target; int /*<<< orphan*/  digests_percent; int /*<<< orphan*/  digests_done; int /*<<< orphan*/  digests_cnt; } ;
typedef  TYPE_2__ hashcat_status_t ;
struct TYPE_89__ {TYPE_1__* status_ctx; } ;
typedef  TYPE_3__ hashcat_ctx_t ;
struct TYPE_90__ {int /*<<< orphan*/  iteration_left_dev; int /*<<< orphan*/  iteration_pos_dev; int /*<<< orphan*/  innerloop_left_dev; int /*<<< orphan*/  innerloop_pos_dev; int /*<<< orphan*/  salt_pos_dev; int /*<<< orphan*/  vector_width_dev; int /*<<< orphan*/  kernel_threads_dev; int /*<<< orphan*/  kernel_loops_dev; int /*<<< orphan*/  kernel_accel_dev; int /*<<< orphan*/  runtime_msec_dev; int /*<<< orphan*/  progress_dev; int /*<<< orphan*/  memoryspeed_dev; int /*<<< orphan*/  corespeed_dev; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  guess_candidates_dev; int /*<<< orphan*/  speed_sec_dev; int /*<<< orphan*/  exec_msec_dev; int /*<<< orphan*/  hashes_msec_dev_benchmark; int /*<<< orphan*/  hashes_msec_dev; int /*<<< orphan*/  skipped_warning_dev; int /*<<< orphan*/  skipped_dev; } ;
typedef  TYPE_4__ device_info_t ;
struct TYPE_91__ {scalar_t__ msec_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_84__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  status_get_corespeed_dev (TYPE_3__*,int) ; 
 int /*<<< orphan*/  status_get_cpt (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_cpt_avg_day (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_cpt_avg_hour (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_cpt_avg_min (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_cpt_cur_day (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_cpt_cur_hour (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_cpt_cur_min (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_device_info_active (TYPE_3__*) ; 
 int status_get_device_info_cnt (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_digests_cnt (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_digests_done (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_digests_percent (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_exec_msec_all (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_exec_msec_dev (TYPE_3__*,int) ; 
 int /*<<< orphan*/  status_get_guess_base (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_guess_base_count (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_guess_base_offset (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_guess_base_percent (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_guess_candidates_dev (TYPE_3__*,int) ; 
 int /*<<< orphan*/  status_get_guess_charset (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_guess_mask_length (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_guess_mod (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_guess_mod_count (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_guess_mod_offset (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_guess_mod_percent (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_guess_mode (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_hash_name (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_hash_target (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_hashes_msec_all (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_hashes_msec_dev (TYPE_3__*,int) ; 
 int /*<<< orphan*/  status_get_hashes_msec_dev_benchmark (TYPE_3__*,int) ; 
 int /*<<< orphan*/  status_get_hwmon_dev (TYPE_3__*,int) ; 
 int /*<<< orphan*/  status_get_innerloop_left_dev (TYPE_3__*,int) ; 
 int /*<<< orphan*/  status_get_innerloop_pos_dev (TYPE_3__*,int) ; 
 int /*<<< orphan*/  status_get_iteration_left_dev (TYPE_3__*,int) ; 
 int /*<<< orphan*/  status_get_iteration_pos_dev (TYPE_3__*,int) ; 
 int /*<<< orphan*/  status_get_kernel_accel_dev (TYPE_3__*,int) ; 
 int /*<<< orphan*/  status_get_kernel_loops_dev (TYPE_3__*,int) ; 
 int /*<<< orphan*/  status_get_kernel_threads_dev (TYPE_3__*,int) ; 
 int /*<<< orphan*/  status_get_memoryspeed_dev (TYPE_3__*,int) ; 
 int /*<<< orphan*/  status_get_msec_paused (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_msec_real (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_msec_running (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_progress_cur (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_progress_cur_relative_skip (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_progress_dev (TYPE_3__*,int) ; 
 int /*<<< orphan*/  status_get_progress_done (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_progress_end (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_progress_end_relative_skip (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_progress_finished_percent (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_progress_ignore (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_progress_mode (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_progress_rejected (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_progress_rejected_percent (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_progress_restored (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_progress_skip (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_restore_percent (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_restore_point (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_restore_total (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_runtime_msec_dev (TYPE_3__*,int) ; 
 int /*<<< orphan*/  status_get_salt_pos_dev (TYPE_3__*,int) ; 
 int /*<<< orphan*/  status_get_salts_cnt (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_salts_done (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_salts_percent (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_session (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_skipped_dev (TYPE_3__*,int) ; 
 int /*<<< orphan*/  status_get_skipped_warning_dev (TYPE_3__*,int) ; 
 int /*<<< orphan*/  status_get_speed_sec_all (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_speed_sec_dev (TYPE_3__*,int) ; 
 int /*<<< orphan*/  status_get_status_number (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_status_string (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_time_estimated_absolute (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_time_estimated_relative (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_time_started_absolute (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_time_started_relative (TYPE_3__*) ; 
 int /*<<< orphan*/  status_get_vector_width_dev (TYPE_3__*,int) ; 

int hashcat_get_status (hashcat_ctx_t *hashcat_ctx, hashcat_status_t *hashcat_status)
{
  const status_ctx_t *status_ctx = hashcat_ctx->status_ctx;

  memset (hashcat_status, 0, sizeof (hashcat_status_t));

  if (status_ctx == NULL) return -1; // way too early

  if (status_ctx->accessible == false)
  {
    if (status_ctx->hashcat_status_final->msec_running > 0)
    {
      memcpy (hashcat_status, status_ctx->hashcat_status_final, sizeof (hashcat_status_t));

      return 0;
    }

    return -1; // still too early
  }

  hashcat_status->digests_cnt                 = status_get_digests_cnt                (hashcat_ctx);
  hashcat_status->digests_done                = status_get_digests_done               (hashcat_ctx);
  hashcat_status->digests_percent             = status_get_digests_percent            (hashcat_ctx);
  hashcat_status->hash_target                 = status_get_hash_target                (hashcat_ctx);
  hashcat_status->hash_name                   = status_get_hash_name                  (hashcat_ctx);
  hashcat_status->guess_base                  = status_get_guess_base                 (hashcat_ctx);
  hashcat_status->guess_base_offset           = status_get_guess_base_offset          (hashcat_ctx);
  hashcat_status->guess_base_count            = status_get_guess_base_count           (hashcat_ctx);
  hashcat_status->guess_base_percent          = status_get_guess_base_percent         (hashcat_ctx);
  hashcat_status->guess_mod                   = status_get_guess_mod                  (hashcat_ctx);
  hashcat_status->guess_mod_offset            = status_get_guess_mod_offset           (hashcat_ctx);
  hashcat_status->guess_mod_count             = status_get_guess_mod_count            (hashcat_ctx);
  hashcat_status->guess_mod_percent           = status_get_guess_mod_percent          (hashcat_ctx);
  hashcat_status->guess_charset               = status_get_guess_charset              (hashcat_ctx);
  hashcat_status->guess_mask_length           = status_get_guess_mask_length          (hashcat_ctx);
  hashcat_status->guess_mode                  = status_get_guess_mode                 (hashcat_ctx);
  hashcat_status->msec_paused                 = status_get_msec_paused                (hashcat_ctx);
  hashcat_status->msec_running                = status_get_msec_running               (hashcat_ctx);
  hashcat_status->msec_real                   = status_get_msec_real                  (hashcat_ctx);
  hashcat_status->progress_mode               = status_get_progress_mode              (hashcat_ctx);
  hashcat_status->progress_finished_percent   = status_get_progress_finished_percent  (hashcat_ctx);
  hashcat_status->progress_cur_relative_skip  = status_get_progress_cur_relative_skip (hashcat_ctx);
  hashcat_status->progress_cur                = status_get_progress_cur               (hashcat_ctx);
  hashcat_status->progress_done               = status_get_progress_done              (hashcat_ctx);
  hashcat_status->progress_end_relative_skip  = status_get_progress_end_relative_skip (hashcat_ctx);
  hashcat_status->progress_end                = status_get_progress_end               (hashcat_ctx);
  hashcat_status->progress_ignore             = status_get_progress_ignore            (hashcat_ctx);
  hashcat_status->progress_rejected           = status_get_progress_rejected          (hashcat_ctx);
  hashcat_status->progress_rejected_percent   = status_get_progress_rejected_percent  (hashcat_ctx);
  hashcat_status->progress_restored           = status_get_progress_restored          (hashcat_ctx);
  hashcat_status->progress_skip               = status_get_progress_skip              (hashcat_ctx);
  hashcat_status->restore_point               = status_get_restore_point              (hashcat_ctx);
  hashcat_status->restore_total               = status_get_restore_total              (hashcat_ctx);
  hashcat_status->restore_percent             = status_get_restore_percent            (hashcat_ctx);
  hashcat_status->salts_cnt                   = status_get_salts_cnt                  (hashcat_ctx);
  hashcat_status->salts_done                  = status_get_salts_done                 (hashcat_ctx);
  hashcat_status->salts_percent               = status_get_salts_percent              (hashcat_ctx);
  hashcat_status->session                     = status_get_session                    (hashcat_ctx);
  #ifdef WITH_BRAIN
  hashcat_status->brain_session               = status_get_brain_session              (hashcat_ctx);
  hashcat_status->brain_attack                = status_get_brain_attack               (hashcat_ctx);
  #endif
  hashcat_status->status_string               = status_get_status_string              (hashcat_ctx);
  hashcat_status->status_number               = status_get_status_number              (hashcat_ctx);
  hashcat_status->time_estimated_absolute     = status_get_time_estimated_absolute    (hashcat_ctx);
  hashcat_status->time_estimated_relative     = status_get_time_estimated_relative    (hashcat_ctx);
  hashcat_status->time_started_absolute       = status_get_time_started_absolute      (hashcat_ctx);
  hashcat_status->time_started_relative       = status_get_time_started_relative      (hashcat_ctx);
  hashcat_status->cpt_cur_min                 = status_get_cpt_cur_min                (hashcat_ctx);
  hashcat_status->cpt_cur_hour                = status_get_cpt_cur_hour               (hashcat_ctx);
  hashcat_status->cpt_cur_day                 = status_get_cpt_cur_day                (hashcat_ctx);
  hashcat_status->cpt_avg_min                 = status_get_cpt_avg_min                (hashcat_ctx);
  hashcat_status->cpt_avg_hour                = status_get_cpt_avg_hour               (hashcat_ctx);
  hashcat_status->cpt_avg_day                 = status_get_cpt_avg_day                (hashcat_ctx);
  hashcat_status->cpt                         = status_get_cpt                        (hashcat_ctx);

  // multiple devices

  hashcat_status->device_info_cnt    = status_get_device_info_cnt    (hashcat_ctx);
  hashcat_status->device_info_active = status_get_device_info_active (hashcat_ctx);

  for (int device_id = 0; device_id < hashcat_status->device_info_cnt; device_id++)
  {
    device_info_t *device_info = hashcat_status->device_info_buf + device_id;

    device_info->skipped_dev                    = status_get_skipped_dev                    (hashcat_ctx, device_id);
    device_info->skipped_warning_dev            = status_get_skipped_warning_dev            (hashcat_ctx, device_id);
    device_info->hashes_msec_dev                = status_get_hashes_msec_dev                (hashcat_ctx, device_id);
    device_info->hashes_msec_dev_benchmark      = status_get_hashes_msec_dev_benchmark      (hashcat_ctx, device_id);
    device_info->exec_msec_dev                  = status_get_exec_msec_dev                  (hashcat_ctx, device_id);
    device_info->speed_sec_dev                  = status_get_speed_sec_dev                  (hashcat_ctx, device_id);
    device_info->guess_candidates_dev           = status_get_guess_candidates_dev           (hashcat_ctx, device_id);
    device_info->hwmon_dev                      = status_get_hwmon_dev                      (hashcat_ctx, device_id);
    device_info->corespeed_dev                  = status_get_corespeed_dev                  (hashcat_ctx, device_id);
    device_info->memoryspeed_dev                = status_get_memoryspeed_dev                (hashcat_ctx, device_id);
    device_info->progress_dev                   = status_get_progress_dev                   (hashcat_ctx, device_id);
    device_info->runtime_msec_dev               = status_get_runtime_msec_dev               (hashcat_ctx, device_id);
    device_info->kernel_accel_dev               = status_get_kernel_accel_dev               (hashcat_ctx, device_id);
    device_info->kernel_loops_dev               = status_get_kernel_loops_dev               (hashcat_ctx, device_id);
    device_info->kernel_threads_dev             = status_get_kernel_threads_dev             (hashcat_ctx, device_id);
    device_info->vector_width_dev               = status_get_vector_width_dev               (hashcat_ctx, device_id);
    device_info->salt_pos_dev                   = status_get_salt_pos_dev                   (hashcat_ctx, device_id);
    device_info->innerloop_pos_dev              = status_get_innerloop_pos_dev              (hashcat_ctx, device_id);
    device_info->innerloop_left_dev             = status_get_innerloop_left_dev             (hashcat_ctx, device_id);
    device_info->iteration_pos_dev              = status_get_iteration_pos_dev              (hashcat_ctx, device_id);
    device_info->iteration_left_dev             = status_get_iteration_left_dev             (hashcat_ctx, device_id);
    #ifdef WITH_BRAIN
    device_info->brain_link_client_id_dev       = status_get_brain_link_client_id_dev       (hashcat_ctx, device_id);
    device_info->brain_link_status_dev          = status_get_brain_link_status_dev          (hashcat_ctx, device_id);
    device_info->brain_link_recv_bytes_dev      = status_get_brain_link_recv_bytes_dev      (hashcat_ctx, device_id);
    device_info->brain_link_send_bytes_dev      = status_get_brain_link_send_bytes_dev      (hashcat_ctx, device_id);
    device_info->brain_link_recv_bytes_sec_dev  = status_get_brain_link_recv_bytes_sec_dev  (hashcat_ctx, device_id);
    device_info->brain_link_send_bytes_sec_dev  = status_get_brain_link_send_bytes_sec_dev  (hashcat_ctx, device_id);
    #endif
  }

  hashcat_status->hashes_msec_all = status_get_hashes_msec_all (hashcat_ctx);
  hashcat_status->exec_msec_all   = status_get_exec_msec_all   (hashcat_ctx);
  hashcat_status->speed_sec_all   = status_get_speed_sec_all   (hashcat_ctx);

  return 0;
}