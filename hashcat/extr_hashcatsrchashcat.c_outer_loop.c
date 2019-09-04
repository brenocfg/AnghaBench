#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_72__   TYPE_9__ ;
typedef  struct TYPE_71__   TYPE_8__ ;
typedef  struct TYPE_70__   TYPE_7__ ;
typedef  struct TYPE_69__   TYPE_6__ ;
typedef  struct TYPE_68__   TYPE_5__ ;
typedef  struct TYPE_67__   TYPE_4__ ;
typedef  struct TYPE_66__   TYPE_3__ ;
typedef  struct TYPE_65__   TYPE_2__ ;
typedef  struct TYPE_64__   TYPE_1__ ;
typedef  struct TYPE_63__   TYPE_13__ ;
typedef  struct TYPE_62__   TYPE_12__ ;
typedef  struct TYPE_61__   TYPE_11__ ;

/* Type definitions */
struct TYPE_64__ {int keyspace; int stdout_flag; int potfile_disable; int loopback; int show; int left; int remove; scalar_t__ skip; scalar_t__ limit; int self_test_disable; int speed_only; int /*<<< orphan*/  hash_mode; } ;
typedef  TYPE_1__ user_options_t ;
typedef  int u32 ;
struct TYPE_65__ {int tid; struct TYPE_65__* hashcat_ctx; TYPE_1__* user_options; TYPE_3__* straight_ctx; TYPE_4__* status_ctx; TYPE_6__* restore_ctx; TYPE_7__* outcheck_ctx; TYPE_8__* opencl_ctx; TYPE_9__* mask_ctx; TYPE_12__* hashes; TYPE_13__* hashconfig; } ;
typedef  TYPE_2__ thread_param_t ;
struct TYPE_66__ {int dicts_cnt; } ;
typedef  TYPE_3__ straight_ctx_t ;
struct TYPE_67__ {scalar_t__ devices_status; int run_main_level2; int run_main_level3; int run_thread_level1; int run_thread_level2; int shutdown_inner; } ;
typedef  TYPE_4__ status_ctx_t ;
struct TYPE_68__ {scalar_t__ masks_pos; } ;
typedef  TYPE_5__ restore_data_t ;
struct TYPE_69__ {TYPE_5__* rd; } ;
typedef  TYPE_6__ restore_ctx_t ;
struct TYPE_70__ {int enabled; } ;
typedef  TYPE_7__ outcheck_ctx_t ;
struct TYPE_71__ {int devices_cnt; int enabled; TYPE_11__* devices_param; } ;
typedef  TYPE_8__ opencl_ctx_t ;
struct TYPE_72__ {int masks_cnt; scalar_t__ masks_pos; } ;
typedef  TYPE_9__ mask_ctx_t ;
typedef  TYPE_2__ hc_thread_t ;
struct TYPE_61__ {int skipped; scalar_t__ st_status; } ;
typedef  TYPE_11__ hc_device_param_t ;
struct TYPE_62__ {scalar_t__ hashes_cnt; scalar_t__ hashes_cnt_orig; scalar_t__ hashlist_mode; scalar_t__ digests_saved; scalar_t__ digests_done; } ;
typedef  TYPE_12__ hashes_t ;
struct TYPE_63__ {int /*<<< orphan*/ * st_pass; int /*<<< orphan*/ * st_hash; } ;
typedef  TYPE_13__ hashconfig_t ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENT_BITMAP_INIT_POST ; 
 int /*<<< orphan*/  EVENT_BITMAP_INIT_PRE ; 
 int /*<<< orphan*/  EVENT_INNERLOOP1_FINISHED ; 
 int /*<<< orphan*/  EVENT_INNERLOOP1_STARTING ; 
 int /*<<< orphan*/  EVENT_OPENCL_SESSION_POST ; 
 int /*<<< orphan*/  EVENT_OPENCL_SESSION_PRE ; 
 int /*<<< orphan*/  EVENT_OUTERLOOP_MAINSCREEN ; 
 int /*<<< orphan*/  EVENT_POTFILE_ALL_CRACKED ; 
 int /*<<< orphan*/  EVENT_POTFILE_NUM_CRACKED ; 
 int /*<<< orphan*/  EVENT_POTFILE_REMOVE_PARSE_POST ; 
 int /*<<< orphan*/  EVENT_POTFILE_REMOVE_PARSE_PRE ; 
 int /*<<< orphan*/  EVENT_SELFTEST_FINISHED ; 
 int /*<<< orphan*/  EVENT_SELFTEST_STARTING ; 
 scalar_t__ HL_MODE_FILE_BINARY ; 
 scalar_t__ HL_MODE_FILE_PLAIN ; 
 scalar_t__ STATUS_CRACKED ; 
 void* STATUS_INIT ; 
 void* STATUS_RUNNING ; 
 scalar_t__ STATUS_SELFTEST ; 
 scalar_t__ ST_STATUS_FAILED ; 
 int /*<<< orphan*/  bitmap_ctx_destroy (TYPE_2__*) ; 
 int bitmap_ctx_init (TYPE_2__*) ; 
 int /*<<< orphan*/  combinator_ctx_destroy (TYPE_2__*) ; 
 int combinator_ctx_init (TYPE_2__*) ; 
 int /*<<< orphan*/  cpt_ctx_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  cpt_ctx_init (TYPE_2__*) ; 
 int /*<<< orphan*/  event_log_error (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  event_log_warning (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  hashconfig_destroy (TYPE_2__*) ; 
 int hashconfig_init (TYPE_2__*) ; 
 int /*<<< orphan*/  hashes_destroy (TYPE_2__*) ; 
 int hashes_init_benchmark (TYPE_2__*) ; 
 int hashes_init_filename (TYPE_2__*) ; 
 int hashes_init_selftest (TYPE_2__*) ; 
 int hashes_init_stage1 (TYPE_2__*) ; 
 int hashes_init_stage2 (TYPE_2__*) ; 
 int hashes_init_stage3 (TYPE_2__*) ; 
 int hashes_init_stage4 (TYPE_2__*) ; 
 int /*<<< orphan*/  hashes_logger (TYPE_2__*) ; 
 int /*<<< orphan*/  hc_thread_create (TYPE_2__,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  hc_thread_wait (int,TYPE_2__*) ; 
 scalar_t__ hccalloc (int,int) ; 
 int /*<<< orphan*/  hcfree (TYPE_2__*) ; 
 int inner1_loop (TYPE_2__*) ; 
 int /*<<< orphan*/  loopback_write_close (TYPE_2__*) ; 
 int /*<<< orphan*/  loopback_write_open (TYPE_2__*) ; 
 int /*<<< orphan*/  mask_ctx_destroy (TYPE_2__*) ; 
 int mask_ctx_init (TYPE_2__*) ; 
 int /*<<< orphan*/  myabort (TYPE_2__*) ; 
 int opencl_session_begin (TYPE_2__*) ; 
 int /*<<< orphan*/  opencl_session_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  outfile_write_close (TYPE_2__*) ; 
 int /*<<< orphan*/  outfile_write_open (TYPE_2__*) ; 
 int potfile_handle_left (TYPE_2__*) ; 
 int potfile_handle_show (TYPE_2__*) ; 
 int /*<<< orphan*/  potfile_remove_parse (TYPE_2__*) ; 
 int /*<<< orphan*/  potfile_write_close (TYPE_2__*) ; 
 int potfile_write_open (TYPE_2__*) ; 
 int save_hash (TYPE_2__*) ; 
 int /*<<< orphan*/  status_progress_destroy (TYPE_2__*) ; 
 int status_progress_init (TYPE_2__*) ; 
 int /*<<< orphan*/  straight_ctx_destroy (TYPE_2__*) ; 
 int straight_ctx_init (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_monitor ; 
 int /*<<< orphan*/  thread_outfile_remove ; 
 int /*<<< orphan*/  thread_selftest ; 
 int /*<<< orphan*/  wl_data_destroy (TYPE_2__*) ; 
 int wl_data_init (TYPE_2__*) ; 

__attribute__((used)) static int outer_loop (hashcat_ctx_t *hashcat_ctx)
{
  hashconfig_t   *hashconfig    = hashcat_ctx->hashconfig;
  hashes_t       *hashes        = hashcat_ctx->hashes;
  mask_ctx_t     *mask_ctx      = hashcat_ctx->mask_ctx;
  opencl_ctx_t   *opencl_ctx    = hashcat_ctx->opencl_ctx;
  outcheck_ctx_t *outcheck_ctx  = hashcat_ctx->outcheck_ctx;
  restore_ctx_t  *restore_ctx   = hashcat_ctx->restore_ctx;
  status_ctx_t   *status_ctx    = hashcat_ctx->status_ctx;
  straight_ctx_t *straight_ctx  = hashcat_ctx->straight_ctx;
  user_options_t *user_options  = hashcat_ctx->user_options;

  status_ctx->devices_status = STATUS_INIT;

  //status_ctx->run_main_level1   = true;
  status_ctx->run_main_level2   = true;
  status_ctx->run_main_level3   = true;
  status_ctx->run_thread_level1 = true;
  status_ctx->run_thread_level2 = true;

  /**
   * setup variables and buffers depending on hash_mode
   */

  const int rc_hashconfig = hashconfig_init (hashcat_ctx);

  if (rc_hashconfig == -1)
  {
    event_log_error (hashcat_ctx, "Invalid hash-mode '%u' selected.", user_options->hash_mode);

    return -1;
  }

  /**
   * generate hashlist filename for later use
   */

  const int rc_hashes_init_filename = hashes_init_filename (hashcat_ctx);

  if (rc_hashes_init_filename == -1) return -1;

  /**
   * load hashes, stage 1
   */

  const int rc_hashes_init_stage1 = hashes_init_stage1 (hashcat_ctx);

  if (rc_hashes_init_stage1 == -1) return -1;

  if ((user_options->keyspace == false) && (user_options->stdout_flag == false))
  {
    if (hashes->hashes_cnt == 0)
    {
      event_log_error (hashcat_ctx, "No hashes loaded.");

      return -1;
    }
  }

  /**
   * load hashes, stage 2, remove duplicates, build base structure
   */

  hashes->hashes_cnt_orig = hashes->hashes_cnt;

  const int rc_hashes_init_stage2 = hashes_init_stage2 (hashcat_ctx);

  if (rc_hashes_init_stage2 == -1) return -1;

  /**
   * potfile removes
   */

  if (user_options->potfile_disable == false)
  {
    EVENT (EVENT_POTFILE_REMOVE_PARSE_PRE);

    if (user_options->loopback == true)
    {
      loopback_write_open (hashcat_ctx);
    }

    potfile_remove_parse (hashcat_ctx);

    if (user_options->loopback == true)
    {
      loopback_write_close (hashcat_ctx);
    }

    EVENT (EVENT_POTFILE_REMOVE_PARSE_POST);
  }

  /**
   * load hashes, stage 3, update cracked results from potfile
   */

  const int rc_hashes_init_stage3 = hashes_init_stage3 (hashcat_ctx);

  if (rc_hashes_init_stage3 == -1) return -1;

  /**
   * potfile show/left handling
   */

  if (user_options->show == true)
  {
    status_ctx->devices_status = STATUS_RUNNING;

    outfile_write_open (hashcat_ctx);

    const int rc = potfile_handle_show (hashcat_ctx);

    if (rc == -1) return -1;

    outfile_write_close (hashcat_ctx);

    return 0;
  }

  if (user_options->left == true)
  {
    status_ctx->devices_status = STATUS_RUNNING;

    outfile_write_open (hashcat_ctx);

    const int rc = potfile_handle_left (hashcat_ctx);

    if (rc == -1) return -1;

    outfile_write_close (hashcat_ctx);

    return 0;
  }

  /**
   * maybe all hashes were cracked, we can exit here
   */

  if (status_ctx->devices_status == STATUS_CRACKED)
  {
    if ((user_options->remove == true) && ((hashes->hashlist_mode == HL_MODE_FILE_PLAIN) || (hashes->hashlist_mode == HL_MODE_FILE_BINARY)))
    {
      if (hashes->digests_saved != hashes->digests_done)
      {
        const int rc = save_hash (hashcat_ctx);

        if (rc == -1) return -1;
      }
    }

    EVENT (EVENT_POTFILE_ALL_CRACKED);

    return 0;
  }

  /**
   * load hashes, stage 4, automatic Optimizers
   */

  const int rc_hashes_init_stage4 = hashes_init_stage4 (hashcat_ctx);

  if (rc_hashes_init_stage4 == -1) return -1;

  /**
   * load hashes, selftest
   */

  const int rc_hashes_init_selftest = hashes_init_selftest (hashcat_ctx);

  if (rc_hashes_init_selftest == -1) return -1;

  /**
   * load hashes, benchmark
   */

  const int rc_hashes_init_benchmark = hashes_init_benchmark (hashcat_ctx);

  if (rc_hashes_init_benchmark == -1) return -1;

  /**
   * Done loading hashes, log results
   */

  hashes_logger (hashcat_ctx);

  /**
   * bitmaps
   */

  EVENT (EVENT_BITMAP_INIT_PRE);

  const int rc_bitmap_init = bitmap_ctx_init (hashcat_ctx);

  if (rc_bitmap_init == -1) return -1;

  EVENT (EVENT_BITMAP_INIT_POST);

  /**
   * cracks-per-time allocate buffer
   */

  cpt_ctx_init (hashcat_ctx);

  /**
   * Wordlist allocate buffer
   */

  const int rc_wl_data_init = wl_data_init (hashcat_ctx);

  if (rc_wl_data_init == -1) return -1;

  /**
   * straight mode init
   */

  const int rc_straight_init = straight_ctx_init (hashcat_ctx);

  if (rc_straight_init == -1) return -1;

  /**
   * straight mode init
   */

  const int rc_combinator_init = combinator_ctx_init (hashcat_ctx);

  if (rc_combinator_init == -1) return -1;

  /**
   * charsets : keep them together for more easy maintainnce
   */

  const int rc_mask_init = mask_ctx_init (hashcat_ctx);

  if (rc_mask_init == -1) return -1;

  /**
   * prevent the user from using --skip/--limit together with maskfile and/or multiple word lists
   */

  if (user_options->skip != 0 || user_options->limit != 0)
  {
    if ((mask_ctx->masks_cnt > 1) || (straight_ctx->dicts_cnt > 1))
    {
      event_log_error (hashcat_ctx, "Use of --skip/--limit is not supported with --increment or mask files.");

      return -1;
    }
  }

  /**
   * prevent the user from using --keyspace together with maskfile and/or multiple word lists
   */

  if (user_options->keyspace == true)
  {
    if ((mask_ctx->masks_cnt > 1) || (straight_ctx->dicts_cnt > 1))
    {
      event_log_error (hashcat_ctx, "Use of --keyspace is not supported with --increment or mask files.");

      return -1;
    }
  }

  /**
   * status progress init; needs hashes that's why we have to do it here and separate from status_ctx_init
   */

  const int rc_status_init = status_progress_init (hashcat_ctx);

  if (rc_status_init == -1) return -1;

  /**
   * main screen
   */

  EVENT (EVENT_OUTERLOOP_MAINSCREEN);

  /**
   * Tell user about cracked hashes by potfile
   */

  EVENT (EVENT_POTFILE_NUM_CRACKED);

  /**
   * inform the user
   */

  EVENT (EVENT_OPENCL_SESSION_PRE);

  const int rc_session_begin = opencl_session_begin (hashcat_ctx);

  if (rc_session_begin == -1) return -1;

  EVENT (EVENT_OPENCL_SESSION_POST);

  /**
   * create self-test threads
   */

  if ((user_options->self_test_disable == false) && (hashconfig->st_hash != NULL) && (hashconfig->st_pass != NULL))
  {
    EVENT (EVENT_SELFTEST_STARTING);

    thread_param_t *threads_param = (thread_param_t *) hccalloc (opencl_ctx->devices_cnt, sizeof (thread_param_t));

    hc_thread_t *selftest_threads = (hc_thread_t *) hccalloc (opencl_ctx->devices_cnt, sizeof (hc_thread_t));

    status_ctx->devices_status = STATUS_SELFTEST;

    for (u32 device_id = 0; device_id < opencl_ctx->devices_cnt; device_id++)
    {
      thread_param_t *thread_param = threads_param + device_id;

      thread_param->hashcat_ctx = hashcat_ctx;
      thread_param->tid         = device_id;

      hc_thread_create (selftest_threads[device_id], thread_selftest, thread_param);
    }

    hc_thread_wait (opencl_ctx->devices_cnt, selftest_threads);

    hcfree (threads_param);

    hcfree (selftest_threads);

    // check for any selftest failures

    for (u32 device_id = 0; device_id < opencl_ctx->devices_cnt; device_id++)
    {
      if (opencl_ctx->enabled == false) continue;

      hc_device_param_t *device_param = opencl_ctx->devices_param + device_id;

      if (device_param->skipped == true) continue;

      if (device_param->st_status == ST_STATUS_FAILED)
      {
        event_log_error (hashcat_ctx, "Aborting session due to kernel self-test failure.");

        event_log_warning (hashcat_ctx, "You can use --self-test-disable to override this, but do not report related errors.");
        event_log_warning (hashcat_ctx, NULL);

        return -1;
      }
    }

    status_ctx->devices_status = STATUS_INIT;

    EVENT (EVENT_SELFTEST_FINISHED);
  }

  /**
   * (old) weak hash check is the first to write to potfile, so open it for writing from here
   * the weak hash check was removed maybe we can move this more to the bottom now
   */

  const int rc_potfile_write = potfile_write_open (hashcat_ctx);

  if (rc_potfile_write == -1) return -1;

  /**
   * status and monitor threads
   */

  int inner_threads_cnt = 0;

  hc_thread_t *inner_threads = (hc_thread_t *) hccalloc (10, sizeof (hc_thread_t));

  status_ctx->shutdown_inner = false;

  /**
    * Outfile remove
    */

  if (user_options->keyspace == false && user_options->stdout_flag == false && user_options->speed_only == false)
  {
    hc_thread_create (inner_threads[inner_threads_cnt], thread_monitor, hashcat_ctx);

    inner_threads_cnt++;

    if (outcheck_ctx->enabled == true)
    {
      hc_thread_create (inner_threads[inner_threads_cnt], thread_outfile_remove, hashcat_ctx);

      inner_threads_cnt++;
    }
  }

  // main call

  if (restore_ctx->rd)
  {
    restore_data_t *rd = restore_ctx->rd;

    if (rd->masks_pos > 0)
    {
      mask_ctx->masks_pos = rd->masks_pos;

      rd->masks_pos = 0;
    }
  }

  EVENT (EVENT_INNERLOOP1_STARTING);

  if (mask_ctx->masks_cnt)
  {
    for (u32 masks_pos = mask_ctx->masks_pos; masks_pos < mask_ctx->masks_cnt; masks_pos++)
    {
      mask_ctx->masks_pos = masks_pos;

      const int rc_inner1_loop = inner1_loop (hashcat_ctx);

      if (rc_inner1_loop == -1) myabort (hashcat_ctx);

      if (status_ctx->run_main_level2 == false) break;
    }

    if (status_ctx->run_main_level2 == true)
    {
      if (mask_ctx->masks_pos + 1 == mask_ctx->masks_cnt) mask_ctx->masks_pos = 0;
    }
  }
  else
  {
    const int rc_inner1_loop = inner1_loop (hashcat_ctx);

    if (rc_inner1_loop == -1) myabort (hashcat_ctx);
  }

  // wait for inner threads

  status_ctx->shutdown_inner = true;

  for (int thread_idx = 0; thread_idx < inner_threads_cnt; thread_idx++)
  {
    hc_thread_wait (1, &inner_threads[thread_idx]);
  }

  hcfree (inner_threads);

  EVENT (EVENT_INNERLOOP1_FINISHED);

  // finalize potfile

  potfile_write_close (hashcat_ctx);

  // finalize opencl session

  opencl_session_destroy (hashcat_ctx);

  // clean up

  bitmap_ctx_destroy      (hashcat_ctx);
  combinator_ctx_destroy  (hashcat_ctx);
  cpt_ctx_destroy         (hashcat_ctx);
  hashconfig_destroy      (hashcat_ctx);
  hashes_destroy          (hashcat_ctx);
  mask_ctx_destroy        (hashcat_ctx);
  status_progress_destroy (hashcat_ctx);
  straight_ctx_destroy    (hashcat_ctx);
  wl_data_destroy         (hashcat_ctx);

  return 0;
}