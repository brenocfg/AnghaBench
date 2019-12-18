#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_9__ ;
typedef  struct TYPE_43__   TYPE_8__ ;
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_1__ ;
typedef  struct TYPE_36__   TYPE_10__ ;

/* Type definitions */
struct TYPE_38__ {int stdout_flag; scalar_t__ attack_mode; int slow_candidates; int speed_only; scalar_t__ hook_threads; } ;
typedef  TYPE_2__ user_options_t ;
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_39__ {int run_thread_level2; } ;
typedef  TYPE_3__ status_ctx_t ;
typedef  int /*<<< orphan*/  pw_t ;
struct TYPE_40__ {int (* module_deep_comp_kernel ) (TYPE_8__*,int const,int) ;} ;
typedef  TYPE_4__ module_ctx_t ;
struct TYPE_41__ {int tid; int tsz; int salt_pos; int pws_cnt; int /*<<< orphan*/  hook_salts_buf; TYPE_7__* device_param; TYPE_3__* status_ctx; TYPE_4__* module_ctx; } ;
typedef  TYPE_5__ hook_thread_param_t ;
typedef  TYPE_5__ hc_thread_t ;
struct TYPE_42__ {int size_tm; int is_cuda; int is_opencl; int const size_hooks; int kernel_loops; int* kernel_params_buf32; int speed_pos; int* speed_cnt; double* speed_msec; double outerloop_multi; int speed_only_finish; int /*<<< orphan*/  opencl_d_hooks; int /*<<< orphan*/  cuda_d_hooks; int /*<<< orphan*/  hooks_buf; int /*<<< orphan*/  opencl_command_queue; int /*<<< orphan*/  timer_speed; int /*<<< orphan*/  opencl_d_pws_buf; int /*<<< orphan*/  opencl_d_pws_amp_buf; int /*<<< orphan*/  cuda_d_pws_amp_buf; int /*<<< orphan*/  cuda_d_pws_buf; int /*<<< orphan*/  opencl_d_bfs_c; int /*<<< orphan*/  opencl_d_tm_c; int /*<<< orphan*/  cuda_d_tm_c; int /*<<< orphan*/  cuda_d_bfs_c; } ;
typedef  TYPE_7__ hc_device_param_t ;
struct TYPE_43__ {TYPE_1__* salts_buf; int /*<<< orphan*/  hook_salts_buf; } ;
typedef  TYPE_8__ hashes_t ;
struct TYPE_44__ {scalar_t__ attack_exec; int opts_type; int opti_type; } ;
typedef  TYPE_9__ hashconfig_t ;
struct TYPE_36__ {TYPE_2__* user_options; TYPE_3__* status_ctx; TYPE_4__* module_ctx; TYPE_8__* hashes; TYPE_9__* hashconfig; } ;
typedef  TYPE_10__ hashcat_ctx_t ;
struct TYPE_37__ {int salt_iter; int salt_iter2; int digests_cnt; } ;

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
 scalar_t__ calloc (int const,int) ; 
 int hc_clEnqueueCopyBuffer (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hc_clEnqueueReadBuffer (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hc_clEnqueueWriteBuffer (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hc_cuMemcpyDtoD (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int hc_cuMemcpyDtoH (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int hc_cuMemcpyHtoD (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  hc_thread_create (TYPE_5__,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  hc_thread_wait (int const,TYPE_5__*) ; 
 double hc_timer_get (int /*<<< orphan*/ ) ; 
 scalar_t__ hccalloc (int const,int) ; 
 int /*<<< orphan*/  hcfree (TYPE_5__*) ; 
 int /*<<< orphan*/  hook12_thread ; 
 int /*<<< orphan*/  hook23_thread ; 
 int process_stdout (TYPE_10__*,TYPE_7__*,int const) ; 
 int run_cuda_kernel_bzero (TYPE_10__*,TYPE_7__*,int /*<<< orphan*/ ,int const) ; 
 int run_kernel (TYPE_10__*,TYPE_7__*,int const,int const,int,int const) ; 
 int run_kernel_amp (TYPE_10__*,TYPE_7__*,int const) ; 
 int run_kernel_tm (TYPE_10__*,TYPE_7__*) ; 
 int run_opencl_kernel_bzero (TYPE_10__*,TYPE_7__*,int /*<<< orphan*/ ,int const) ; 
 int stub1 (TYPE_8__*,int const,int) ; 

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
          const u32 size_tm = device_param->size_tm;

          if (device_param->is_cuda == true)
          {
            if (run_cuda_kernel_bzero (hashcat_ctx, device_param, device_param->cuda_d_tm_c, size_tm) == -1) return -1;
          }

          if (device_param->is_opencl == true)
          {
            if (run_opencl_kernel_bzero (hashcat_ctx, device_param, device_param->opencl_d_tm_c, size_tm) == -1) return -1;
          }

          if (run_kernel_tm (hashcat_ctx, device_param) == -1) return -1;

          if (device_param->is_cuda == true)
          {
            if (hc_cuMemcpyDtoD (hashcat_ctx, device_param->cuda_d_bfs_c, device_param->cuda_d_tm_c, size_tm) == -1) return -1;
          }

          if (device_param->is_opencl == true)
          {
            if (hc_clEnqueueCopyBuffer (hashcat_ctx, device_param->opencl_command_queue, device_param->opencl_d_tm_c, device_param->opencl_d_bfs_c, 0, 0, size_tm, 0, NULL, NULL) == -1) return -1;
          }
        }
      }
    }

    if (hashconfig->opti_type & OPTI_TYPE_OPTIMIZED_KERNEL)
    {
      if (highest_pw_len < 16)
      {
        if (run_kernel (hashcat_ctx, device_param, KERN_RUN_1, pws_cnt, true, fast_iteration) == -1) return -1;
      }
      else if (highest_pw_len < 32)
      {
        if (run_kernel (hashcat_ctx, device_param, KERN_RUN_2, pws_cnt, true, fast_iteration) == -1) return -1;
      }
      else
      {
        if (run_kernel (hashcat_ctx, device_param, KERN_RUN_3, pws_cnt, true, fast_iteration) == -1) return -1;
      }
    }
    else
    {
      if (run_kernel (hashcat_ctx, device_param, KERN_RUN_4, pws_cnt, true, fast_iteration) == -1) return -1;
    }
  }
  else
  {
    bool run_init = true;
    bool run_loop = true;
    bool run_comp = true;

    if (run_init == true)
    {
      if (device_param->is_cuda == true)
      {
        if (hc_cuMemcpyDtoD (hashcat_ctx, device_param->cuda_d_pws_buf, device_param->cuda_d_pws_amp_buf, pws_cnt * sizeof (pw_t)) == -1) return -1;
      }

      if (device_param->is_opencl == true)
      {
        if (hc_clEnqueueCopyBuffer (hashcat_ctx, device_param->opencl_command_queue, device_param->opencl_d_pws_amp_buf, device_param->opencl_d_pws_buf, 0, 0, pws_cnt * sizeof (pw_t), 0, NULL, NULL) == -1) return -1;
      }

      if (user_options->slow_candidates == true)
      {
      }
      else
      {
        if (run_kernel_amp (hashcat_ctx, device_param, pws_cnt) == -1) return -1;
      }

      if (run_kernel (hashcat_ctx, device_param, KERN_RUN_1, pws_cnt, false, 0) == -1) return -1;

      if (hashconfig->opts_type & OPTS_TYPE_HOOK12)
      {
        if (run_kernel (hashcat_ctx, device_param, KERN_RUN_12, pws_cnt, false, 0) == -1) return -1;

        if (device_param->is_cuda == true)
        {
          if (hc_cuMemcpyDtoH (hashcat_ctx, device_param->hooks_buf, device_param->cuda_d_hooks, device_param->size_hooks) == -1) return -1;
        }

        if (device_param->is_opencl == true)
        {
          if (hc_clEnqueueReadBuffer (hashcat_ctx, device_param->opencl_command_queue, device_param->opencl_d_hooks, CL_TRUE, 0, device_param->size_hooks, device_param->hooks_buf, 0, NULL, NULL) == -1) return -1;
        }

        const int hook_threads = (int) user_options->hook_threads;

        hook_thread_param_t *hook_threads_param = (hook_thread_param_t *) hccalloc (hook_threads, sizeof (hook_thread_param_t));

        for (int i = 0; i < hook_threads; i++)
        {
          hook_thread_param_t *hook_thread_param = hook_threads_param + i;

          hook_thread_param->tid = i;
          hook_thread_param->tsz = hook_threads;

          hook_thread_param->module_ctx = module_ctx;
          hook_thread_param->status_ctx = status_ctx;

          hook_thread_param->device_param = device_param;

          hook_thread_param->hook_salts_buf = hashes->hook_salts_buf;

          hook_thread_param->salt_pos = salt_pos;

          hook_thread_param->pws_cnt = pws_cnt;
        }

        hc_thread_t *c_threads = (hc_thread_t *) calloc (hook_threads, sizeof (hc_thread_t));

        for (int i = 0; i < hook_threads; i++)
        {
          hook_thread_param_t *hook_thread_param = hook_threads_param + i;

          hc_thread_create (c_threads[i], hook12_thread, hook_thread_param);
        }

        hc_thread_wait (hook_threads, c_threads);

        hcfree (c_threads);

        hcfree (hook_threads_param);

        if (device_param->is_cuda == true)
        {
          if (hc_cuMemcpyHtoD (hashcat_ctx, device_param->cuda_d_hooks, device_param->hooks_buf, device_param->size_hooks) == -1) return -1;
        }

        if (device_param->is_opencl == true)
        {
          if (hc_clEnqueueWriteBuffer (hashcat_ctx, device_param->opencl_command_queue, device_param->opencl_d_hooks, CL_TRUE, 0, device_param->size_hooks, device_param->hooks_buf, 0, NULL, NULL) == -1) return -1;
        }
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

        if (run_kernel (hashcat_ctx, device_param, KERN_RUN_2, pws_cnt, true, slow_iteration) == -1) return -1;

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
        if (run_kernel (hashcat_ctx, device_param, KERN_RUN_23, pws_cnt, false, 0) == -1) return -1;

        if (device_param->is_cuda == true)
        {
          if (hc_cuMemcpyDtoH (hashcat_ctx, device_param->hooks_buf, device_param->cuda_d_hooks, device_param->size_hooks) == -1) return -1;
        }

        if (device_param->is_opencl == true)
        {
          if (hc_clEnqueueReadBuffer (hashcat_ctx, device_param->opencl_command_queue, device_param->opencl_d_hooks, CL_TRUE, 0, device_param->size_hooks, device_param->hooks_buf, 0, NULL, NULL) == -1) return -1;
        }

        const int hook_threads = (int) user_options->hook_threads;

        hook_thread_param_t *hook_threads_param = (hook_thread_param_t *) hccalloc (hook_threads, sizeof (hook_thread_param_t));

        for (int i = 0; i < hook_threads; i++)
        {
          hook_thread_param_t *hook_thread_param = hook_threads_param + i;

          hook_thread_param->tid = i;
          hook_thread_param->tsz = hook_threads;

          hook_thread_param->module_ctx = module_ctx;
          hook_thread_param->status_ctx = status_ctx;

          hook_thread_param->device_param = device_param;

          hook_thread_param->hook_salts_buf = hashes->hook_salts_buf;

          hook_thread_param->salt_pos = salt_pos;

          hook_thread_param->pws_cnt = pws_cnt;
        }

        hc_thread_t *c_threads = (hc_thread_t *) calloc (hook_threads, sizeof (hc_thread_t));

        for (int i = 0; i < hook_threads; i++)
        {
          hook_thread_param_t *hook_thread_param = hook_threads_param + i;

          hc_thread_create (c_threads[i], hook23_thread, hook_thread_param);
        }

        hc_thread_wait (hook_threads, c_threads);

        hcfree (c_threads);

        hcfree (hook_threads_param);

        if (device_param->is_cuda == true)
        {
          if (hc_cuMemcpyHtoD (hashcat_ctx, device_param->cuda_d_hooks, device_param->hooks_buf, device_param->size_hooks) == -1) return -1;
        }

        if (device_param->is_opencl == true)
        {
          if (hc_clEnqueueWriteBuffer (hashcat_ctx, device_param->opencl_command_queue, device_param->opencl_d_hooks, CL_TRUE, 0, device_param->size_hooks, device_param->hooks_buf, 0, NULL, NULL) == -1) return -1;
        }
      }
    }

    // init2 and loop2 are kind of special, we use run_loop for them, too

    if (run_loop == true)
    {
      // note: they also do not influence the performance screen
      // in case you want to use this, this cane make sense only if your input data comes out of tmps[]

      if (hashconfig->opts_type & OPTS_TYPE_INIT2)
      {
        if (run_kernel (hashcat_ctx, device_param, KERN_RUN_INIT2, pws_cnt, false, 0) == -1) return -1;
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

          if (run_kernel (hashcat_ctx, device_param, KERN_RUN_LOOP2, pws_cnt, true, slow_iteration) == -1) return -1;

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

          if (run_kernel (hashcat_ctx, device_param, deep_comp_kernel, pws_cnt, false, 0) == -1) return -1;

          if (status_ctx->run_thread_level2 == false) break;
        }
      }
      else
      {
        if (run_kernel (hashcat_ctx, device_param, KERN_RUN_3, pws_cnt, false, 0) == -1) return -1;
      }
    }

    /*
     * maybe we should add this zero of temporary buffers
     * however it drops the performance from 7055338 to 7010621

    if (device_param->is_cuda == true)
    {
      if (run_cuda_kernel_bzero   (hashcat_ctx, device_param, device_param->cuda_d_tmps,   device_param->size_tmps) == -1) return -1;
    }

    if (device_param->is_opencl == true)
    {
      if (run_opencl_kernel_bzero (hashcat_ctx, device_param, device_param->opencl_d_tmps, device_param->size_tmps) == -1) return -1;
    }
    */

    if ((hashconfig->opts_type & OPTS_TYPE_HOOK12) || (hashconfig->opts_type & OPTS_TYPE_HOOK23))
    {
      if (device_param->is_cuda == true)
      {
        if (run_cuda_kernel_bzero   (hashcat_ctx, device_param, device_param->cuda_d_hooks,   device_param->size_hooks) == -1) return -1;
      }

      if (device_param->is_opencl == true)
      {
        if (run_opencl_kernel_bzero (hashcat_ctx, device_param, device_param->opencl_d_hooks, device_param->size_hooks) == -1) return -1;
      }
    }
  }

  return 0;
}