#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_10__ {int enabled; size_t devices_cnt; TYPE_2__* devices_param; } ;
typedef  TYPE_1__ opencl_ctx_t ;
struct TYPE_11__ {int skipped; int /*<<< orphan*/ * context; int /*<<< orphan*/ * command_queue; int /*<<< orphan*/ * program_amp; int /*<<< orphan*/ * program_mp; int /*<<< orphan*/ * program; int /*<<< orphan*/ * kernel_aux4; int /*<<< orphan*/ * kernel_aux3; int /*<<< orphan*/ * kernel_aux2; int /*<<< orphan*/ * kernel_aux1; int /*<<< orphan*/ * kernel_decompress; int /*<<< orphan*/ * kernel_atinit; int /*<<< orphan*/ * kernel_memset; int /*<<< orphan*/ * kernel_amp; int /*<<< orphan*/ * kernel_tm; int /*<<< orphan*/ * kernel_mp_r; int /*<<< orphan*/ * kernel_mp_l; int /*<<< orphan*/ * kernel_mp; int /*<<< orphan*/ * kernel_loop2; int /*<<< orphan*/ * kernel_init2; int /*<<< orphan*/ * kernel4; int /*<<< orphan*/ * kernel3; int /*<<< orphan*/ * kernel23; int /*<<< orphan*/ * kernel2; int /*<<< orphan*/ * kernel12; int /*<<< orphan*/ * kernel1; int /*<<< orphan*/ * d_st_esalts_buf; int /*<<< orphan*/ * d_st_salts_buf; int /*<<< orphan*/ * d_st_digests_buf; int /*<<< orphan*/ * d_tm_c; int /*<<< orphan*/ * d_markov_css_buf; int /*<<< orphan*/ * d_root_css_buf; int /*<<< orphan*/ * d_extra3_buf; int /*<<< orphan*/ * d_extra2_buf; int /*<<< orphan*/ * d_extra1_buf; int /*<<< orphan*/ * d_extra0_buf; int /*<<< orphan*/ * d_result; int /*<<< orphan*/ * d_hooks; int /*<<< orphan*/ * d_tmps; int /*<<< orphan*/ * d_esalt_bufs; int /*<<< orphan*/ * d_salt_bufs; int /*<<< orphan*/ * d_digests_shown; int /*<<< orphan*/ * d_digests_buf; int /*<<< orphan*/ * d_plain_bufs; int /*<<< orphan*/ * d_bitmap_s2_d; int /*<<< orphan*/ * d_bitmap_s2_c; int /*<<< orphan*/ * d_bitmap_s2_b; int /*<<< orphan*/ * d_bitmap_s2_a; int /*<<< orphan*/ * d_bitmap_s1_d; int /*<<< orphan*/ * d_bitmap_s1_c; int /*<<< orphan*/ * d_bitmap_s1_b; int /*<<< orphan*/ * d_bitmap_s1_a; int /*<<< orphan*/ * d_bfs_c; int /*<<< orphan*/ * d_bfs; int /*<<< orphan*/ * d_combs_c; int /*<<< orphan*/ * d_combs; int /*<<< orphan*/ * d_rules_c; int /*<<< orphan*/ * d_rules; int /*<<< orphan*/ * d_pws_idx; int /*<<< orphan*/ * d_pws_comp_buf; int /*<<< orphan*/ * d_pws_amp_buf; int /*<<< orphan*/ * d_pws_buf; int /*<<< orphan*/ * scratch_buf; int /*<<< orphan*/ * hooks_buf; int /*<<< orphan*/ * combs_buf; int /*<<< orphan*/ * pws_base_buf; int /*<<< orphan*/ * pws_pre_buf; int /*<<< orphan*/ * pws_idx; int /*<<< orphan*/ * pws_comp; } ;
typedef  TYPE_2__ hc_device_param_t ;
struct TYPE_12__ {TYPE_1__* opencl_ctx; } ;
typedef  TYPE_3__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  hc_clReleaseCommandQueue (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hc_clReleaseContext (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hc_clReleaseKernel (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hc_clReleaseMemObject (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hc_clReleaseProgram (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hcfree (int /*<<< orphan*/ *) ; 

void opencl_session_destroy (hashcat_ctx_t *hashcat_ctx)
{
  opencl_ctx_t *opencl_ctx = hashcat_ctx->opencl_ctx;

  if (opencl_ctx->enabled == false) return;

  for (u32 device_id = 0; device_id < opencl_ctx->devices_cnt; device_id++)
  {
    hc_device_param_t *device_param = &opencl_ctx->devices_param[device_id];

    if (device_param->skipped == true) continue;

    hcfree (device_param->pws_comp);
    hcfree (device_param->pws_idx);
    hcfree (device_param->pws_pre_buf);
    hcfree (device_param->pws_base_buf);
    hcfree (device_param->combs_buf);
    hcfree (device_param->hooks_buf);
    hcfree (device_param->scratch_buf);
    #ifdef WITH_BRAIN
    hcfree (device_param->brain_link_in_buf);
    hcfree (device_param->brain_link_out_buf);
    #endif

    if (device_param->d_pws_buf)        hc_clReleaseMemObject (hashcat_ctx, device_param->d_pws_buf);
    if (device_param->d_pws_amp_buf)    hc_clReleaseMemObject (hashcat_ctx, device_param->d_pws_amp_buf);
    if (device_param->d_pws_comp_buf)   hc_clReleaseMemObject (hashcat_ctx, device_param->d_pws_comp_buf);
    if (device_param->d_pws_idx)        hc_clReleaseMemObject (hashcat_ctx, device_param->d_pws_idx);
    if (device_param->d_rules)          hc_clReleaseMemObject (hashcat_ctx, device_param->d_rules);
    if (device_param->d_rules_c)        hc_clReleaseMemObject (hashcat_ctx, device_param->d_rules_c);
    if (device_param->d_combs)          hc_clReleaseMemObject (hashcat_ctx, device_param->d_combs);
    if (device_param->d_combs_c)        hc_clReleaseMemObject (hashcat_ctx, device_param->d_combs_c);
    if (device_param->d_bfs)            hc_clReleaseMemObject (hashcat_ctx, device_param->d_bfs);
    if (device_param->d_bfs_c)          hc_clReleaseMemObject (hashcat_ctx, device_param->d_bfs_c);
    if (device_param->d_bitmap_s1_a)    hc_clReleaseMemObject (hashcat_ctx, device_param->d_bitmap_s1_a);
    if (device_param->d_bitmap_s1_b)    hc_clReleaseMemObject (hashcat_ctx, device_param->d_bitmap_s1_b);
    if (device_param->d_bitmap_s1_c)    hc_clReleaseMemObject (hashcat_ctx, device_param->d_bitmap_s1_c);
    if (device_param->d_bitmap_s1_d)    hc_clReleaseMemObject (hashcat_ctx, device_param->d_bitmap_s1_d);
    if (device_param->d_bitmap_s2_a)    hc_clReleaseMemObject (hashcat_ctx, device_param->d_bitmap_s2_a);
    if (device_param->d_bitmap_s2_b)    hc_clReleaseMemObject (hashcat_ctx, device_param->d_bitmap_s2_b);
    if (device_param->d_bitmap_s2_c)    hc_clReleaseMemObject (hashcat_ctx, device_param->d_bitmap_s2_c);
    if (device_param->d_bitmap_s2_d)    hc_clReleaseMemObject (hashcat_ctx, device_param->d_bitmap_s2_d);
    if (device_param->d_plain_bufs)     hc_clReleaseMemObject (hashcat_ctx, device_param->d_plain_bufs);
    if (device_param->d_digests_buf)    hc_clReleaseMemObject (hashcat_ctx, device_param->d_digests_buf);
    if (device_param->d_digests_shown)  hc_clReleaseMemObject (hashcat_ctx, device_param->d_digests_shown);
    if (device_param->d_salt_bufs)      hc_clReleaseMemObject (hashcat_ctx, device_param->d_salt_bufs);
    if (device_param->d_esalt_bufs)     hc_clReleaseMemObject (hashcat_ctx, device_param->d_esalt_bufs);
    if (device_param->d_tmps)           hc_clReleaseMemObject (hashcat_ctx, device_param->d_tmps);
    if (device_param->d_hooks)          hc_clReleaseMemObject (hashcat_ctx, device_param->d_hooks);
    if (device_param->d_result)         hc_clReleaseMemObject (hashcat_ctx, device_param->d_result);
    if (device_param->d_extra0_buf)     hc_clReleaseMemObject (hashcat_ctx, device_param->d_extra0_buf);
    if (device_param->d_extra1_buf)     hc_clReleaseMemObject (hashcat_ctx, device_param->d_extra1_buf);
    if (device_param->d_extra2_buf)     hc_clReleaseMemObject (hashcat_ctx, device_param->d_extra2_buf);
    if (device_param->d_extra3_buf)     hc_clReleaseMemObject (hashcat_ctx, device_param->d_extra3_buf);
    if (device_param->d_root_css_buf)   hc_clReleaseMemObject (hashcat_ctx, device_param->d_root_css_buf);
    if (device_param->d_markov_css_buf) hc_clReleaseMemObject (hashcat_ctx, device_param->d_markov_css_buf);
    if (device_param->d_tm_c)           hc_clReleaseMemObject (hashcat_ctx, device_param->d_tm_c);
    if (device_param->d_st_digests_buf) hc_clReleaseMemObject (hashcat_ctx, device_param->d_st_digests_buf);
    if (device_param->d_st_salts_buf)   hc_clReleaseMemObject (hashcat_ctx, device_param->d_st_salts_buf);
    if (device_param->d_st_esalts_buf)  hc_clReleaseMemObject (hashcat_ctx, device_param->d_st_esalts_buf);

    if (device_param->kernel1)          hc_clReleaseKernel (hashcat_ctx, device_param->kernel1);
    if (device_param->kernel12)         hc_clReleaseKernel (hashcat_ctx, device_param->kernel12);
    if (device_param->kernel2)          hc_clReleaseKernel (hashcat_ctx, device_param->kernel2);
    if (device_param->kernel23)         hc_clReleaseKernel (hashcat_ctx, device_param->kernel23);
    if (device_param->kernel3)          hc_clReleaseKernel (hashcat_ctx, device_param->kernel3);
    if (device_param->kernel4)          hc_clReleaseKernel (hashcat_ctx, device_param->kernel4);
    if (device_param->kernel_init2)     hc_clReleaseKernel (hashcat_ctx, device_param->kernel_init2);
    if (device_param->kernel_loop2)     hc_clReleaseKernel (hashcat_ctx, device_param->kernel_loop2);
    if (device_param->kernel_mp)        hc_clReleaseKernel (hashcat_ctx, device_param->kernel_mp);
    if (device_param->kernel_mp_l)      hc_clReleaseKernel (hashcat_ctx, device_param->kernel_mp_l);
    if (device_param->kernel_mp_r)      hc_clReleaseKernel (hashcat_ctx, device_param->kernel_mp_r);
    if (device_param->kernel_tm)        hc_clReleaseKernel (hashcat_ctx, device_param->kernel_tm);
    if (device_param->kernel_amp)       hc_clReleaseKernel (hashcat_ctx, device_param->kernel_amp);
    if (device_param->kernel_memset)    hc_clReleaseKernel (hashcat_ctx, device_param->kernel_memset);
    if (device_param->kernel_atinit)    hc_clReleaseKernel (hashcat_ctx, device_param->kernel_atinit);
    if (device_param->kernel_decompress)hc_clReleaseKernel (hashcat_ctx, device_param->kernel_decompress);
    if (device_param->kernel_aux1)      hc_clReleaseKernel (hashcat_ctx, device_param->kernel_aux1);
    if (device_param->kernel_aux2)      hc_clReleaseKernel (hashcat_ctx, device_param->kernel_aux2);
    if (device_param->kernel_aux3)      hc_clReleaseKernel (hashcat_ctx, device_param->kernel_aux3);
    if (device_param->kernel_aux4)      hc_clReleaseKernel (hashcat_ctx, device_param->kernel_aux4);

    if (device_param->program)          hc_clReleaseProgram (hashcat_ctx, device_param->program);
    if (device_param->program_mp)       hc_clReleaseProgram (hashcat_ctx, device_param->program_mp);
    if (device_param->program_amp)      hc_clReleaseProgram (hashcat_ctx, device_param->program_amp);

    if (device_param->command_queue)    hc_clReleaseCommandQueue (hashcat_ctx, device_param->command_queue);

    if (device_param->context)          hc_clReleaseContext (hashcat_ctx, device_param->context);

    device_param->pws_comp            = NULL;
    device_param->pws_idx             = NULL;
    device_param->pws_pre_buf         = NULL;
    device_param->pws_base_buf        = NULL;
    device_param->combs_buf           = NULL;
    device_param->hooks_buf           = NULL;
    device_param->scratch_buf         = NULL;
    #ifdef WITH_BRAIN
    device_param->brain_link_in_buf   = NULL;
    device_param->brain_link_out_buf  = NULL;
    #endif

    device_param->d_pws_buf           = NULL;
    device_param->d_pws_amp_buf       = NULL;
    device_param->d_pws_comp_buf      = NULL;
    device_param->d_pws_idx           = NULL;
    device_param->d_rules             = NULL;
    device_param->d_rules_c           = NULL;
    device_param->d_combs             = NULL;
    device_param->d_combs_c           = NULL;
    device_param->d_bfs               = NULL;
    device_param->d_bfs_c             = NULL;
    device_param->d_bitmap_s1_a       = NULL;
    device_param->d_bitmap_s1_b       = NULL;
    device_param->d_bitmap_s1_c       = NULL;
    device_param->d_bitmap_s1_d       = NULL;
    device_param->d_bitmap_s2_a       = NULL;
    device_param->d_bitmap_s2_b       = NULL;
    device_param->d_bitmap_s2_c       = NULL;
    device_param->d_bitmap_s2_d       = NULL;
    device_param->d_plain_bufs        = NULL;
    device_param->d_digests_buf       = NULL;
    device_param->d_digests_shown     = NULL;
    device_param->d_salt_bufs         = NULL;
    device_param->d_esalt_bufs        = NULL;
    device_param->d_tmps              = NULL;
    device_param->d_hooks             = NULL;
    device_param->d_result            = NULL;
    device_param->d_extra0_buf        = NULL;
    device_param->d_extra1_buf        = NULL;
    device_param->d_extra2_buf        = NULL;
    device_param->d_extra3_buf        = NULL;
    device_param->d_root_css_buf      = NULL;
    device_param->d_markov_css_buf    = NULL;
    device_param->d_tm_c              = NULL;
    device_param->d_st_digests_buf    = NULL;
    device_param->d_st_salts_buf      = NULL;
    device_param->d_st_esalts_buf     = NULL;
    device_param->kernel1             = NULL;
    device_param->kernel12            = NULL;
    device_param->kernel2             = NULL;
    device_param->kernel23            = NULL;
    device_param->kernel3             = NULL;
    device_param->kernel4             = NULL;
    device_param->kernel_init2        = NULL;
    device_param->kernel_loop2        = NULL;
    device_param->kernel_mp           = NULL;
    device_param->kernel_mp_l         = NULL;
    device_param->kernel_mp_r         = NULL;
    device_param->kernel_tm           = NULL;
    device_param->kernel_amp          = NULL;
    device_param->kernel_memset       = NULL;
    device_param->kernel_atinit       = NULL;
    device_param->kernel_decompress   = NULL;
    device_param->kernel_aux1         = NULL;
    device_param->kernel_aux2         = NULL;
    device_param->kernel_aux3         = NULL;
    device_param->kernel_aux4         = NULL;
    device_param->program             = NULL;
    device_param->program_mp          = NULL;
    device_param->program_amp         = NULL;
    device_param->command_queue       = NULL;
    device_param->context             = NULL;
  }
}