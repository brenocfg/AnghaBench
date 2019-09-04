#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_15__ ;

/* Type definitions */
struct TYPE_19__ {int slow_candidates; scalar_t__ attack_mode; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_20__ {scalar_t__ attack_kern; } ;
typedef  TYPE_2__ user_options_extra_t ;
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_21__ {int off; } ;
typedef  TYPE_3__ pw_idx_t ;
struct TYPE_18__ {scalar_t__ tv_sec; } ;
struct TYPE_22__ {int words_off; int* kernel_params_mp_buf64; int* kernel_params_mp_l_buf64; TYPE_3__* pws_comp; int /*<<< orphan*/  d_pws_comp_buf; int /*<<< orphan*/  command_queue; TYPE_3__* pws_idx; int /*<<< orphan*/  d_pws_idx; TYPE_15__ timer_speed; } ;
typedef  TYPE_4__ hc_device_param_t ;
struct TYPE_23__ {int opti_type; int opts_type; } ;
typedef  TYPE_5__ hashconfig_t ;
struct TYPE_24__ {TYPE_2__* user_options_extra; TYPE_1__* user_options; TYPE_5__* hashconfig; TYPE_7__* combinator_ctx; } ;
typedef  TYPE_6__ hashcat_ctx_t ;
struct TYPE_25__ {scalar_t__ combs_mode; } ;
typedef  TYPE_7__ combinator_ctx_t ;

/* Variables and functions */
 scalar_t__ ATTACK_KERN_BF ; 
 scalar_t__ ATTACK_KERN_COMBI ; 
 scalar_t__ ATTACK_KERN_STRAIGHT ; 
 scalar_t__ ATTACK_MODE_COMBI ; 
 scalar_t__ ATTACK_MODE_HYBRID1 ; 
 scalar_t__ ATTACK_MODE_HYBRID2 ; 
 int /*<<< orphan*/  CL_TRUE ; 
 scalar_t__ COMBINATOR_MODE_BASE_RIGHT ; 
 int /*<<< orphan*/  KERN_RUN_MP ; 
 int /*<<< orphan*/  KERN_RUN_MP_L ; 
 int OPTI_TYPE_OPTIMIZED_KERNEL ; 
 int OPTS_TYPE_PT_ADD01 ; 
 int OPTS_TYPE_PT_ADD06 ; 
 int OPTS_TYPE_PT_ADD80 ; 
 int hc_clEnqueueWriteBuffer (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hc_timer_set (TYPE_15__*) ; 
 int /*<<< orphan*/  rebuild_pws_compressed_append (TYPE_4__*,int const,int) ; 
 int run_kernel_decompress (TYPE_6__*,TYPE_4__*,int const) ; 
 int run_kernel_mp (TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ ,int const) ; 

int run_copy (hashcat_ctx_t *hashcat_ctx, hc_device_param_t *device_param, const u64 pws_cnt)
{
  combinator_ctx_t     *combinator_ctx      = hashcat_ctx->combinator_ctx;
  hashconfig_t         *hashconfig          = hashcat_ctx->hashconfig;
  user_options_t       *user_options        = hashcat_ctx->user_options;
  user_options_extra_t *user_options_extra  = hashcat_ctx->user_options_extra;

  // init speed timer

  #if defined (_WIN)
  if (device_param->timer_speed.QuadPart == 0)
  {
    hc_timer_set (&device_param->timer_speed);
  }
  #else
  if (device_param->timer_speed.tv_sec == 0)
  {
    hc_timer_set (&device_param->timer_speed);
  }
  #endif

  if (user_options->slow_candidates == true)
  {
    int CL_rc;

    CL_rc = hc_clEnqueueWriteBuffer (hashcat_ctx, device_param->command_queue, device_param->d_pws_idx, CL_TRUE, 0, pws_cnt * sizeof (pw_idx_t), device_param->pws_idx, 0, NULL, NULL);

    if (CL_rc == -1) return -1;

    const pw_idx_t *pw_idx = device_param->pws_idx + pws_cnt;

    const u32 off = pw_idx->off;

    if (off)
    {
      CL_rc = hc_clEnqueueWriteBuffer (hashcat_ctx, device_param->command_queue, device_param->d_pws_comp_buf, CL_TRUE, 0, off * sizeof (u32), device_param->pws_comp, 0, NULL, NULL);

      if (CL_rc == -1) return -1;
    }

    CL_rc = run_kernel_decompress (hashcat_ctx, device_param, pws_cnt);

    if (CL_rc == -1) return -1;
  }
  else
  {
    if (user_options_extra->attack_kern == ATTACK_KERN_STRAIGHT)
    {
      int CL_rc;

      CL_rc = hc_clEnqueueWriteBuffer (hashcat_ctx, device_param->command_queue, device_param->d_pws_idx, CL_TRUE, 0, pws_cnt * sizeof (pw_idx_t), device_param->pws_idx, 0, NULL, NULL);

      if (CL_rc == -1) return -1;

      const pw_idx_t *pw_idx = device_param->pws_idx + pws_cnt;

      const u32 off = pw_idx->off;

      if (off)
      {
        CL_rc = hc_clEnqueueWriteBuffer (hashcat_ctx, device_param->command_queue, device_param->d_pws_comp_buf, CL_TRUE, 0, off * sizeof (u32), device_param->pws_comp, 0, NULL, NULL);

        if (CL_rc == -1) return -1;
      }

      CL_rc = run_kernel_decompress (hashcat_ctx, device_param, pws_cnt);

      if (CL_rc == -1) return -1;
    }
    else if (user_options_extra->attack_kern == ATTACK_KERN_COMBI)
    {
      if (hashconfig->opti_type & OPTI_TYPE_OPTIMIZED_KERNEL)
      {
        if (user_options->attack_mode == ATTACK_MODE_COMBI)
        {
          if (combinator_ctx->combs_mode == COMBINATOR_MODE_BASE_RIGHT)
          {
            if (hashconfig->opts_type & OPTS_TYPE_PT_ADD01)
            {
              rebuild_pws_compressed_append (device_param, pws_cnt, 0x01);
            }
            else if (hashconfig->opts_type & OPTS_TYPE_PT_ADD06)
            {
              rebuild_pws_compressed_append (device_param, pws_cnt, 0x06);
            }
            else if (hashconfig->opts_type & OPTS_TYPE_PT_ADD80)
            {
              rebuild_pws_compressed_append (device_param, pws_cnt, 0x80);
            }
          }
        }
        else if (user_options->attack_mode == ATTACK_MODE_HYBRID2)
        {
          if (hashconfig->opts_type & OPTS_TYPE_PT_ADD01)
          {
            rebuild_pws_compressed_append (device_param, pws_cnt, 0x01);
          }
          else if (hashconfig->opts_type & OPTS_TYPE_PT_ADD06)
          {
            rebuild_pws_compressed_append (device_param, pws_cnt, 0x06);
          }
          else if (hashconfig->opts_type & OPTS_TYPE_PT_ADD80)
          {
            rebuild_pws_compressed_append (device_param, pws_cnt, 0x80);
          }
        }

        int CL_rc;

        CL_rc = hc_clEnqueueWriteBuffer (hashcat_ctx, device_param->command_queue, device_param->d_pws_idx, CL_TRUE, 0, pws_cnt * sizeof (pw_idx_t), device_param->pws_idx, 0, NULL, NULL);

        if (CL_rc == -1) return -1;

        const pw_idx_t *pw_idx = device_param->pws_idx + pws_cnt;

        const u32 off = pw_idx->off;

        if (off)
        {
          CL_rc = hc_clEnqueueWriteBuffer (hashcat_ctx, device_param->command_queue, device_param->d_pws_comp_buf, CL_TRUE, 0, off * sizeof (u32), device_param->pws_comp, 0, NULL, NULL);

          if (CL_rc == -1) return -1;
        }

        CL_rc = run_kernel_decompress (hashcat_ctx, device_param, pws_cnt);

        if (CL_rc == -1) return -1;
      }
      else
      {
        if (user_options->attack_mode == ATTACK_MODE_COMBI)
        {
          int CL_rc;

          CL_rc = hc_clEnqueueWriteBuffer (hashcat_ctx, device_param->command_queue, device_param->d_pws_idx, CL_TRUE, 0, pws_cnt * sizeof (pw_idx_t), device_param->pws_idx, 0, NULL, NULL);

          if (CL_rc == -1) return -1;

          const pw_idx_t *pw_idx = device_param->pws_idx + pws_cnt;

          const u32 off = pw_idx->off;

          if (off)
          {
            CL_rc = hc_clEnqueueWriteBuffer (hashcat_ctx, device_param->command_queue, device_param->d_pws_comp_buf, CL_TRUE, 0, off * sizeof (u32), device_param->pws_comp, 0, NULL, NULL);

            if (CL_rc == -1) return -1;
          }

          CL_rc = run_kernel_decompress (hashcat_ctx, device_param, pws_cnt);

          if (CL_rc == -1) return -1;
        }
        else if (user_options->attack_mode == ATTACK_MODE_HYBRID1)
        {
          int CL_rc;

          CL_rc = hc_clEnqueueWriteBuffer (hashcat_ctx, device_param->command_queue, device_param->d_pws_idx, CL_TRUE, 0, pws_cnt * sizeof (pw_idx_t), device_param->pws_idx, 0, NULL, NULL);

          if (CL_rc == -1) return -1;

          const pw_idx_t *pw_idx = device_param->pws_idx + pws_cnt;

          const u32 off = pw_idx->off;

          if (off)
          {
            CL_rc = hc_clEnqueueWriteBuffer (hashcat_ctx, device_param->command_queue, device_param->d_pws_comp_buf, CL_TRUE, 0, off * sizeof (u32), device_param->pws_comp, 0, NULL, NULL);

            if (CL_rc == -1) return -1;
          }

          CL_rc = run_kernel_decompress (hashcat_ctx, device_param, pws_cnt);

          if (CL_rc == -1) return -1;
        }
        else if (user_options->attack_mode == ATTACK_MODE_HYBRID2)
        {
          const u64 off = device_param->words_off;

          device_param->kernel_params_mp_buf64[3] = off;

          const int CL_rc = run_kernel_mp (hashcat_ctx, device_param, KERN_RUN_MP, pws_cnt);

          if (CL_rc == -1) return -1;
        }
      }
    }
    else if (user_options_extra->attack_kern == ATTACK_KERN_BF)
    {
      const u64 off = device_param->words_off;

      device_param->kernel_params_mp_l_buf64[3] = off;

      const int CL_rc = run_kernel_mp (hashcat_ctx, device_param, KERN_RUN_MP_L, pws_cnt);

      if (CL_rc == -1) return -1;
    }
  }

  return 0;
}