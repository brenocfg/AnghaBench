#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {int stdout_flag; scalar_t__ attack_mode; int slow_candidates; int speed_only; } ;
typedef  TYPE_2__ user_options_t ;
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_29__ {int run_thread_level2; } ;
typedef  TYPE_3__ status_ctx_t ;
typedef  int /*<<< orphan*/  pw_t ;
struct TYPE_30__ {int (* module_deep_comp_kernel ) (TYPE_6__*,int const,int) ;int /*<<< orphan*/  (* module_hook23 ) (TYPE_5__*,int /*<<< orphan*/ ,int const,int const) ;int /*<<< orphan*/  (* module_hook12 ) (TYPE_5__*,int /*<<< orphan*/ ,int const,int const) ;} ;
typedef  TYPE_4__ module_ctx_t ;
struct TYPE_31__ {int kernel_loops; int* kernel_params_buf32; int speed_pos; int* speed_cnt; double* speed_msec; double outerloop_multi; int speed_only_finish; int /*<<< orphan*/  hooks_buf; int /*<<< orphan*/  size_hooks; int /*<<< orphan*/  d_hooks; int /*<<< orphan*/  command_queue; int /*<<< orphan*/  timer_speed; int /*<<< orphan*/  d_pws_buf; int /*<<< orphan*/  d_pws_amp_buf; int /*<<< orphan*/  d_bfs_c; int /*<<< orphan*/  d_tm_c; } ;
typedef  TYPE_5__ hc_device_param_t ;
struct TYPE_32__ {TYPE_1__* salts_buf; int /*<<< orphan*/  hook_salts_buf; } ;
typedef  TYPE_6__ hashes_t ;
struct TYPE_33__ {scalar_t__ attack_exec; int opts_type; int opti_type; } ;
typedef  TYPE_7__ hashconfig_t ;
struct TYPE_34__ {TYPE_2__* user_options; TYPE_3__* status_ctx; TYPE_4__* module_ctx; TYPE_6__* hashes; TYPE_7__* hashconfig; } ;
typedef  TYPE_8__ hashcat_ctx_t ;
typedef  int /*<<< orphan*/  bs_word_t ;
struct TYPE_27__ {int salt_iter; int salt_iter2; int digests_cnt; } ;

/* Variables and functions */
 scalar_t__ ATTACK_EXEC_INSIDE_KERNEL ; 
 scalar_t__ ATTACK_MODE_BF ; 
 int /*<<< orphan*/  CL_TRUE ; 
 int const KERN_RUN_1 ; 
 int const KERN_RUN_12 ; 
 int const KERN_RUN_2 ; 
 int const KERN_RUN_23 ; 
 int const KERN_RUN_3 ; 
 int const KERN_RUN_4 ; 
 int const KERN_RUN_INIT2 ; 
 int const KERN_RUN_LOOP2 ; 
 int MIN (int,int) ; 
 int OPTI_TYPE_OPTIMIZED_KERNEL ; 
 int OPTS_TYPE_DEEP_COMP_KERNEL ; 
 int OPTS_TYPE_HOOK12 ; 
 int OPTS_TYPE_HOOK23 ; 
 int OPTS_TYPE_INIT2 ; 
 int OPTS_TYPE_LOOP2 ; 
 int OPTS_TYPE_PT_BITSLICE ; 
 int hc_clEnqueueCopyBuffer (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hc_clEnqueueReadBuffer (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hc_clEnqueueWriteBuffer (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 double hc_timer_get (int /*<<< orphan*/ ) ; 
 int process_stdout (TYPE_8__*,TYPE_5__*,int const) ; 
 int run_kernel (TYPE_8__*,TYPE_5__*,int const,int const,int,int const) ; 
 int run_kernel_amp (TYPE_8__*,TYPE_5__*,int const) ; 
 int run_kernel_bzero (TYPE_8__*,TYPE_5__*,int /*<<< orphan*/ ,int const) ; 
 int run_kernel_tm (TYPE_8__*,TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ,int const,int const) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int /*<<< orphan*/ ,int const,int const) ; 
 int stub3 (TYPE_6__*,int const,int) ; 

int choose_kernel (hashcat_ctx_t *hashcat_ctx, hc_device_param_t *device_param, const u32 highest_pw_len, const u64 pws_cnt, const u32 fast_iteration, const u32 salt_pos)
{
  hashconfig_t   *hashconfig   = hashcat_ctx->hashconfig;
  hashes_t       *hashes       = hashcat_ctx->hashes;
  module_ctx_t   *module_ctx   = hashcat_ctx->module_ctx;
  status_ctx_t   *status_ctx   = hashcat_ctx->status_ctx;
  user_options_t *user_options = hashcat_ctx->user_options;

  if (user_options->stdout_flag == true)
  {
    return process_stdout (hashcat_ctx, device_param, pws_cnt);
  }

  int CL_rc;

  if (hashconfig->attack_exec == ATTACK_EXEC_INSIDE_KERNEL)
  {
    if (user_options->attack_mode == ATTACK_MODE_BF)
    {
      if (user_options->slow_candidates == true)
      {
      }
      else
      {
        if (hashconfig->opts_type & OPTS_TYPE_PT_BITSLICE)
        {
          const u32 size_tm = 32 * sizeof (bs_word_t);

          CL_rc = run_kernel_bzero (hashcat_ctx, device_param, device_param->d_tm_c, size_tm);

          if (CL_rc == -1) return -1;

          CL_rc = run_kernel_tm (hashcat_ctx, device_param);

          if (CL_rc == -1) return -1;

          CL_rc = hc_clEnqueueCopyBuffer (hashcat_ctx, device_param->command_queue, device_param->d_tm_c, device_param->d_bfs_c, 0, 0, size_tm, 0, NULL, NULL);

          if (CL_rc == -1) return -1;
        }
      }
    }

    if (hashconfig->opti_type & OPTI_TYPE_OPTIMIZED_KERNEL)
    {
      if (highest_pw_len < 16)
      {
        CL_rc = run_kernel (hashcat_ctx, device_param, KERN_RUN_1, pws_cnt, true, fast_iteration);

        if (CL_rc == -1) return -1;
      }
      else if (highest_pw_len < 32)
      {
        CL_rc = run_kernel (hashcat_ctx, device_param, KERN_RUN_2, pws_cnt, true, fast_iteration);

        if (CL_rc == -1) return -1;
      }
      else
      {
        CL_rc = run_kernel (hashcat_ctx, device_param, KERN_RUN_3, pws_cnt, true, fast_iteration);

        if (CL_rc == -1) return -1;
      }
    }
    else
    {
      CL_rc = run_kernel (hashcat_ctx, device_param, KERN_RUN_4, pws_cnt, true, fast_iteration);

      if (CL_rc == -1) return -1;
    }
  }
  else
  {
    bool run_init = true;
    bool run_loop = true;
    bool run_comp = true;

    if (run_init == true)
    {
      CL_rc = hc_clEnqueueCopyBuffer (hashcat_ctx, device_param->command_queue, device_param->d_pws_amp_buf, device_param->d_pws_buf, 0, 0, pws_cnt * sizeof (pw_t), 0, NULL, NULL);

      if (CL_rc == -1) return -1;

      if (user_options->slow_candidates == true)
      {
      }
      else
      {
        CL_rc = run_kernel_amp (hashcat_ctx, device_param, pws_cnt);

        if (CL_rc == -1) return -1;
      }

      CL_rc = run_kernel (hashcat_ctx, device_param, KERN_RUN_1, pws_cnt, false, 0);

      if (CL_rc == -1) return -1;

      if (hashconfig->opts_type & OPTS_TYPE_HOOK12)
      {
        CL_rc = run_kernel (hashcat_ctx, device_param, KERN_RUN_12, pws_cnt, false, 0);

        if (CL_rc == -1) return -1;

        CL_rc = hc_clEnqueueReadBuffer (hashcat_ctx, device_param->command_queue, device_param->d_hooks, CL_TRUE, 0, device_param->size_hooks, device_param->hooks_buf, 0, NULL, NULL);

        if (CL_rc == -1) return -1;

        module_ctx->module_hook12 (device_param, hashes->hook_salts_buf, salt_pos, pws_cnt);

        CL_rc = hc_clEnqueueWriteBuffer (hashcat_ctx, device_param->command_queue, device_param->d_hooks, CL_TRUE, 0, device_param->size_hooks, device_param->hooks_buf, 0, NULL, NULL);

        if (CL_rc == -1) return -1;
      }
    }

    if (run_loop == true)
    {
      u32 iter = hashes->salts_buf[salt_pos].salt_iter;

      u32 loop_step = device_param->kernel_loops;

      for (u32 loop_pos = 0, slow_iteration = 0; loop_pos < iter; loop_pos += loop_step, slow_iteration++)
      {
        u32 loop_left = iter - loop_pos;

        loop_left = MIN (loop_left, loop_step);

        device_param->kernel_params_buf32[28] = loop_pos;
        device_param->kernel_params_buf32[29] = loop_left;

        CL_rc = run_kernel (hashcat_ctx, device_param, KERN_RUN_2, pws_cnt, true, slow_iteration);

        if (CL_rc == -1) return -1;

        //bug?
        //while (status_ctx->run_thread_level2 == false) break;
        if (status_ctx->run_thread_level2 == false) break;

        /**
         * speed
         */

        const float iter_part = (float) (loop_pos + loop_left) / iter;

        const u64 perf_sum_all = (u64) (pws_cnt * iter_part);

        double speed_msec = hc_timer_get (device_param->timer_speed);

        const u32 speed_pos = device_param->speed_pos;

        device_param->speed_cnt[speed_pos] = perf_sum_all;

        device_param->speed_msec[speed_pos] = speed_msec;

        if (user_options->speed_only == true)
        {
          if (speed_msec > 4000)
          {
            device_param->outerloop_multi *= (double) iter / (double) (loop_pos + loop_left);

            device_param->speed_pos = 1;

            device_param->speed_only_finish = true;

            return 0;
          }
        }
      }

      if (hashconfig->opts_type & OPTS_TYPE_HOOK23)
      {
        CL_rc = run_kernel (hashcat_ctx, device_param, KERN_RUN_23, pws_cnt, false, 0);

        if (CL_rc == -1) return -1;

        CL_rc = hc_clEnqueueReadBuffer (hashcat_ctx, device_param->command_queue, device_param->d_hooks, CL_TRUE, 0, device_param->size_hooks, device_param->hooks_buf, 0, NULL, NULL);

        if (CL_rc == -1) return -1;

        module_ctx->module_hook23 (device_param, hashes->hook_salts_buf, salt_pos, pws_cnt);

        CL_rc = hc_clEnqueueWriteBuffer (hashcat_ctx, device_param->command_queue, device_param->d_hooks, CL_TRUE, 0, device_param->size_hooks, device_param->hooks_buf, 0, NULL, NULL);

        if (CL_rc == -1) return -1;
      }
    }

    // init2 and loop2 are kind of special, we use run_loop for them, too

    if (run_loop == true)
    {
      // note: they also do not influence the performance screen
      // in case you want to use this, this cane make sense only if your input data comes out of tmps[]

      if (hashconfig->opts_type & OPTS_TYPE_INIT2)
      {
        CL_rc = run_kernel (hashcat_ctx, device_param, KERN_RUN_INIT2, pws_cnt, false, 0);

        if (CL_rc == -1) return -1;
      }

      if (hashconfig->opts_type & OPTS_TYPE_LOOP2)
      {
        u32 iter = hashes->salts_buf[salt_pos].salt_iter2;

        u32 loop_step = device_param->kernel_loops;

        for (u32 loop_pos = 0, slow_iteration = 0; loop_pos < iter; loop_pos += loop_step, slow_iteration++)
        {
          u32 loop_left = iter - loop_pos;

          loop_left = MIN (loop_left, loop_step);

          device_param->kernel_params_buf32[28] = loop_pos;
          device_param->kernel_params_buf32[29] = loop_left;

          CL_rc = run_kernel (hashcat_ctx, device_param, KERN_RUN_LOOP2, pws_cnt, true, slow_iteration);

          if (CL_rc == -1) return -1;

          //bug?
          //while (status_ctx->run_thread_level2 == false) break;
          if (status_ctx->run_thread_level2 == false) break;
        }
      }
    }

    if (run_comp == true)
    {
      if (hashconfig->opts_type & OPTS_TYPE_DEEP_COMP_KERNEL)
      {
        const u32 loops_cnt = hashes->salts_buf[salt_pos].digests_cnt;

        for (u32 loops_pos = 0; loops_pos < loops_cnt; loops_pos++)
        {
          device_param->kernel_params_buf32[28] = loops_pos;
          device_param->kernel_params_buf32[29] = loops_cnt;

          const u32 deep_comp_kernel = module_ctx->module_deep_comp_kernel (hashes, salt_pos, loops_pos);

          CL_rc = run_kernel (hashcat_ctx, device_param, deep_comp_kernel, pws_cnt, false, 0);

          if (CL_rc == -1) return -1;

          if (status_ctx->run_thread_level2 == false) break;
        }
      }
      else
      {
        CL_rc = run_kernel (hashcat_ctx, device_param, KERN_RUN_3, pws_cnt, false, 0);

        if (CL_rc == -1) return -1;
      }
    }
  }

  return 0;
}