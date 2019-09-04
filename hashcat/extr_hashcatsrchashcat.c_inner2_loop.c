#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_8__ ;
typedef  struct TYPE_43__   TYPE_7__ ;
typedef  struct TYPE_42__   TYPE_6__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_1__ ;
typedef  struct TYPE_36__   TYPE_11__ ;
typedef  struct TYPE_35__   TYPE_10__ ;

/* Type definitions */
struct TYPE_37__ {scalar_t__ skip; int keyspace; int loopback; int speed_only; int progress_only; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_38__ {scalar_t__ wordlist_mode; } ;
typedef  TYPE_2__ user_options_extra_t ;
typedef  int u64 ;
typedef  size_t u32 ;
typedef  void* time_t ;
struct TYPE_39__ {size_t tid; TYPE_11__* hashcat_ctx; } ;
typedef  TYPE_3__ thread_param_t ;
struct TYPE_40__ {int run_thread_level1; int run_thread_level2; scalar_t__ devices_status; scalar_t__ words_off; scalar_t__ words_cur; int words_base; int const words_cnt; int* words_progress_restored; int accessible; int checkpoint_shutdown; int run_main_level3; int /*<<< orphan*/  hashcat_status_final; void* runtime_stop; void* runtime_start; int /*<<< orphan*/  timer_running; scalar_t__ msec_paused; } ;
typedef  TYPE_4__ status_ctx_t ;
struct TYPE_41__ {scalar_t__ words_cur; } ;
typedef  TYPE_5__ restore_data_t ;
struct TYPE_42__ {TYPE_5__* rd; } ;
typedef  TYPE_6__ restore_ctx_t ;
struct TYPE_43__ {size_t devices_cnt; } ;
typedef  TYPE_7__ opencl_ctx_t ;
typedef  int /*<<< orphan*/  logfile_ctx_t ;
struct TYPE_44__ {scalar_t__ induction_dictionaries_cnt; scalar_t__ induction_dictionaries_pos; TYPE_3__* induction_dictionaries; } ;
typedef  TYPE_8__ induct_ctx_t ;
typedef  TYPE_3__ hc_thread_t ;
struct TYPE_35__ {size_t salts_cnt; } ;
typedef  TYPE_10__ hashes_t ;
struct TYPE_36__ {TYPE_1__* user_options; TYPE_2__* user_options_extra; TYPE_4__* status_ctx; TYPE_6__* restore_ctx; TYPE_7__* opencl_ctx; int /*<<< orphan*/ * logfile_ctx; TYPE_8__* induct_ctx; TYPE_10__* hashes; } ;
typedef  TYPE_11__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENT_AUTOTUNE_FINISHED ; 
 int /*<<< orphan*/  EVENT_AUTOTUNE_STARTING ; 
 int /*<<< orphan*/  EVENT_CALCULATED_WORDS_BASE ; 
 int /*<<< orphan*/  EVENT_CRACKER_FINISHED ; 
 int /*<<< orphan*/  EVENT_CRACKER_STARTING ; 
 scalar_t__ STATUS_ABORTED ; 
 scalar_t__ STATUS_ABORTED_CHECKPOINT ; 
 scalar_t__ STATUS_ABORTED_RUNTIME ; 
 scalar_t__ STATUS_AUTOTUNE ; 
 scalar_t__ STATUS_BYPASS ; 
 scalar_t__ STATUS_CRACKED ; 
 scalar_t__ STATUS_ERROR ; 
 scalar_t__ STATUS_EXHAUSTED ; 
 scalar_t__ STATUS_INIT ; 
 scalar_t__ STATUS_QUIT ; 
 scalar_t__ STATUS_RUNNING ; 
 scalar_t__ WL_MODE_STDIN ; 
 int /*<<< orphan*/  cpt_ctx_reset (TYPE_11__*) ; 
 int /*<<< orphan*/  event_log_error (TYPE_11__*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int hashcat_get_status (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hc_thread_create (TYPE_3__,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  hc_thread_wait (size_t,TYPE_3__*) ; 
 int /*<<< orphan*/  hc_timer_set (int /*<<< orphan*/ *) ; 
 scalar_t__ hccalloc (size_t,int) ; 
 int /*<<< orphan*/  hcfree (TYPE_3__*) ; 
 int /*<<< orphan*/  induct_ctx_scan (TYPE_11__*) ; 
 int /*<<< orphan*/  logfile_generate_subid (TYPE_11__*) ; 
 int /*<<< orphan*/  logfile_sub_msg (char*) ; 
 int /*<<< orphan*/  logfile_sub_uint (void*) ; 
 int /*<<< orphan*/  logfile_sub_var_uint (char*,scalar_t__) ; 
 int /*<<< orphan*/  loopback_write_close (TYPE_11__*) ; 
 int /*<<< orphan*/  loopback_write_open (TYPE_11__*) ; 
 int mask_ctx_update_loop (TYPE_11__*) ; 
 int /*<<< orphan*/  myabort (TYPE_11__*) ; 
 int /*<<< orphan*/  myabort_checkpoint (TYPE_11__*) ; 
 int /*<<< orphan*/  opencl_ctx_devices_kernel_loops (TYPE_11__*) ; 
 int /*<<< orphan*/  opencl_ctx_devices_sync_tuning (TYPE_11__*) ; 
 int /*<<< orphan*/  opencl_ctx_devices_update_power (TYPE_11__*) ; 
 int /*<<< orphan*/  opencl_session_reset (TYPE_11__*) ; 
 int /*<<< orphan*/  status_progress_reset (TYPE_11__*) ; 
 int /*<<< orphan*/  stderr ; 
 int straight_ctx_update_loop (TYPE_11__*) ; 
 int /*<<< orphan*/  thread_autotune ; 
 int /*<<< orphan*/  thread_calc ; 
 int /*<<< orphan*/  thread_calc_stdin ; 
 int /*<<< orphan*/  time (void**) ; 
 int /*<<< orphan*/  unlink (TYPE_3__) ; 
 int user_options_extra_amplifier (TYPE_11__*) ; 

__attribute__((used)) static int inner2_loop (hashcat_ctx_t *hashcat_ctx)
{
  hashes_t             *hashes              = hashcat_ctx->hashes;
  induct_ctx_t         *induct_ctx          = hashcat_ctx->induct_ctx;
  logfile_ctx_t        *logfile_ctx         = hashcat_ctx->logfile_ctx;
  opencl_ctx_t         *opencl_ctx          = hashcat_ctx->opencl_ctx;
  restore_ctx_t        *restore_ctx         = hashcat_ctx->restore_ctx;
  status_ctx_t         *status_ctx          = hashcat_ctx->status_ctx;
  user_options_extra_t *user_options_extra  = hashcat_ctx->user_options_extra;
  user_options_t       *user_options        = hashcat_ctx->user_options;

  //status_ctx->run_main_level1   = true;
  //status_ctx->run_main_level2   = true;
  //status_ctx->run_main_level3   = true;
  status_ctx->run_thread_level1 = true;
  status_ctx->run_thread_level2 = true;

  status_ctx->devices_status = STATUS_INIT;

  logfile_generate_subid (hashcat_ctx);

  logfile_sub_msg ("START");

  status_progress_reset (hashcat_ctx);

  status_ctx->msec_paused = 0;

  status_ctx->words_off = 0;
  status_ctx->words_cur = 0;

  if (restore_ctx->rd)
  {
    restore_data_t *rd = restore_ctx->rd;

    if (rd->words_cur > 0)
    {
      status_ctx->words_off = rd->words_cur;
      status_ctx->words_cur = status_ctx->words_off;

      rd->words_cur = 0;

      // --restore always overrides --skip

      user_options->skip = 0;
    }
  }

  if (user_options->skip > 0)
  {
    status_ctx->words_off = user_options->skip;
    status_ctx->words_cur = status_ctx->words_off;

    user_options->skip = 0;
  }

  opencl_session_reset (hashcat_ctx);

  cpt_ctx_reset (hashcat_ctx);

  /**
   * Update attack-mode specific stuff based on mask
   */

  const int rc_mask_ctx_update_loop = mask_ctx_update_loop (hashcat_ctx);

  if (rc_mask_ctx_update_loop == -1) return 0;

  /**
   * Update attack-mode specific stuff based on wordlist
   */

  const int rc_straight_ctx_update_loop = straight_ctx_update_loop (hashcat_ctx);

  if (rc_straight_ctx_update_loop == -1) return 0;

  // words base

  const u64 amplifier_cnt = user_options_extra_amplifier (hashcat_ctx);

  status_ctx->words_base = status_ctx->words_cnt / amplifier_cnt;

  EVENT (EVENT_CALCULATED_WORDS_BASE);

  if (user_options->keyspace == true)
  {
    status_ctx->devices_status = STATUS_RUNNING;

    return 0;
  }

  // restore stuff

  if (status_ctx->words_off > status_ctx->words_base)
  {
    event_log_error (hashcat_ctx, "Restore value is greater than keyspace.");

    return -1;
  }

  const u64 progress_restored = status_ctx->words_off * amplifier_cnt;

  for (u32 i = 0; i < hashes->salts_cnt; i++)
  {
    status_ctx->words_progress_restored[i] = progress_restored;
  }

  #ifdef WITH_BRAIN
  if (user_options->brain_client == true)
  {
    user_options->brain_attack = brain_compute_attack (hashcat_ctx);
  }
  #endif

  /**
   * limit kernel loops by the amplification count we have from:
   * - straight_ctx, combinator_ctx or mask_ctx for fast hashes
   * - hash iteration count for slow hashes
   * this is required for autotune
   */

  opencl_ctx_devices_kernel_loops (hashcat_ctx);

  /**
   * prepare thread buffers
   */

  thread_param_t *threads_param = (thread_param_t *) hccalloc (opencl_ctx->devices_cnt, sizeof (thread_param_t));

  hc_thread_t *c_threads = (hc_thread_t *) hccalloc (opencl_ctx->devices_cnt, sizeof (hc_thread_t));

  /**
   * create autotune threads
   */

  EVENT (EVENT_AUTOTUNE_STARTING);

  status_ctx->devices_status = STATUS_AUTOTUNE;

  for (u32 device_id = 0; device_id < opencl_ctx->devices_cnt; device_id++)
  {
    thread_param_t *thread_param = threads_param + device_id;

    thread_param->hashcat_ctx = hashcat_ctx;
    thread_param->tid         = device_id;

    hc_thread_create (c_threads[device_id], thread_autotune, thread_param);
  }

  hc_thread_wait (opencl_ctx->devices_cnt, c_threads);

  EVENT (EVENT_AUTOTUNE_FINISHED);

  /**
   * find same opencl devices and equal results
   */

  opencl_ctx_devices_sync_tuning (hashcat_ctx);

  /**
   * autotune modified kernel_accel, which modifies opencl_ctx->kernel_power_all
   */

  opencl_ctx_devices_update_power (hashcat_ctx);

  /**
   * Begin loopback recording
   */

  if (user_options->loopback == true)
  {
    loopback_write_open (hashcat_ctx);
  }

  /**
   * Prepare cracking stats
   */

  hc_timer_set (&status_ctx->timer_running);

  time_t runtime_start;

  time (&runtime_start);

  status_ctx->runtime_start = runtime_start;

  /**
   * create cracker threads
   */

  EVENT (EVENT_CRACKER_STARTING);

  status_ctx->devices_status = STATUS_RUNNING;

  status_ctx->accessible = true;

  for (u32 device_id = 0; device_id < opencl_ctx->devices_cnt; device_id++)
  {
    thread_param_t *thread_param = threads_param + device_id;

    thread_param->hashcat_ctx = hashcat_ctx;
    thread_param->tid         = device_id;

    if (user_options_extra->wordlist_mode == WL_MODE_STDIN)
    {
      hc_thread_create (c_threads[device_id], thread_calc_stdin, thread_param);
    }
    else
    {
      hc_thread_create (c_threads[device_id], thread_calc, thread_param);
    }
  }

  hc_thread_wait (opencl_ctx->devices_cnt, c_threads);

  hcfree (c_threads);

  hcfree (threads_param);

  if ((status_ctx->devices_status == STATUS_RUNNING) && (status_ctx->checkpoint_shutdown == true))
  {
    myabort_checkpoint (hashcat_ctx);
  }

  if ((status_ctx->devices_status != STATUS_CRACKED)
   && (status_ctx->devices_status != STATUS_ERROR)
   && (status_ctx->devices_status != STATUS_ABORTED)
   && (status_ctx->devices_status != STATUS_ABORTED_CHECKPOINT)
   && (status_ctx->devices_status != STATUS_ABORTED_RUNTIME)
   && (status_ctx->devices_status != STATUS_QUIT)
   && (status_ctx->devices_status != STATUS_BYPASS))
  {
    status_ctx->devices_status = STATUS_EXHAUSTED;
  }

  if (status_ctx->devices_status == STATUS_EXHAUSTED)
  {
    // the options speed-only and progress-only cause hashcat to abort quickly.
    // therefore, they will end up (if no other error occured) as STATUS_EXHAUSTED.
    // however, that can create confusion in hashcats RC, because exhausted translates to RC = 1.
    // but then having RC = 1 does not match our expection if we use for speed-only and progress-only.
    // to get hashcat to return RC = 0 we have to set it to CRACKED or BYPASS
    // note: other options like --show, --left, --benchmark, --keyspace, --opencl-info, etc.
    // not not reach this section of the code, they've returned already with rc 0.

    if ((user_options->speed_only == true) || (user_options->progress_only == true))
    {
      status_ctx->devices_status = STATUS_BYPASS;
    }
  }

  // update some timer

  time_t runtime_stop;

  time (&runtime_stop);

  status_ctx->runtime_stop = runtime_stop;

  logfile_sub_uint (runtime_start);
  logfile_sub_uint (runtime_stop);

  if (hashcat_get_status (hashcat_ctx, status_ctx->hashcat_status_final) == -1)
  {
    fprintf (stderr, "Initialization problem: the hashcat status monitoring function returned an unexpected value\n");
  }

  status_ctx->accessible = false;

  EVENT (EVENT_CRACKER_FINISHED);

  // mark sub logfile

  logfile_sub_var_uint ("status-after-work", status_ctx->devices_status);

  logfile_sub_msg ("STOP");

  // stop loopback recording

  if (user_options->loopback == true)
  {
    loopback_write_close (hashcat_ctx);
  }

  // New induction folder check, which is a controlled recursion

  if (induct_ctx->induction_dictionaries_cnt == 0)
  {
    induct_ctx_scan (hashcat_ctx);

    while (induct_ctx->induction_dictionaries_cnt)
    {
      for (induct_ctx->induction_dictionaries_pos = 0; induct_ctx->induction_dictionaries_pos < induct_ctx->induction_dictionaries_cnt; induct_ctx->induction_dictionaries_pos++)
      {
        if (status_ctx->devices_status == STATUS_EXHAUSTED)
        {
          const int rc_inner2_loop = inner2_loop (hashcat_ctx);

          if (rc_inner2_loop == -1) myabort (hashcat_ctx);

          if (status_ctx->run_main_level3 == false) break;
        }

        unlink (induct_ctx->induction_dictionaries[induct_ctx->induction_dictionaries_pos]);
      }

      hcfree (induct_ctx->induction_dictionaries);

      induct_ctx_scan (hashcat_ctx);
    }
  }

  return 0;
}