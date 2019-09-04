#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_219__   TYPE_6__ ;
typedef  struct TYPE_218__   TYPE_5__ ;
typedef  struct TYPE_217__   TYPE_4__ ;
typedef  struct TYPE_216__   TYPE_3__ ;
typedef  struct TYPE_215__   TYPE_2__ ;
typedef  struct TYPE_214__   TYPE_1__ ;

/* Type definitions */
struct TYPE_214__ {int quiet; int example_hashes; int optimized_kernel_enable; int /*<<< orphan*/  slow_candidates; scalar_t__ keep_guessing; scalar_t__ hex_salt; scalar_t__ keyboard_layout_mapping; int /*<<< orphan*/  hash_mode; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_215__ {int /*<<< orphan*/  attack_kern; } ;
typedef  TYPE_2__ user_options_extra_t ;
struct TYPE_216__ {scalar_t__ module_context_size; scalar_t__ module_interface_version; int (* module_attack_exec ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_benchmark_mask ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_dictstat_disable ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_dgst_pos0 ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_dgst_pos1 ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_dgst_pos2 ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_dgst_pos3 ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_dgst_size ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_esalt_size ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_forced_outfile_format ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_hash_category ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_hash_name ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_hash_mode ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_hlfmt_disable ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_hook_salt_size ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_hook_size ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_kernel_accel_min ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_kernel_accel_max ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_kernel_loops_min ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_kernel_loops_max ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_kernel_threads_min ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_kernel_threads_max ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_kern_type ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_kern_type_dynamic ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_opti_type ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_opts_type ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_outfile_check_disable ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_outfile_check_nocomp ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_potfile_disable ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_potfile_keep_all_hashes ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_pwdump_column ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_pw_min ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_pw_max ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_salt_min ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_salt_max ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_salt_type ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_separator ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_st_hash ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_st_pass ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_tmp_size ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_warmup_disable ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_hash_decode ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int (* module_hash_encode ) (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ;int /*<<< orphan*/ * module_build_plain_postprocess; int /*<<< orphan*/ * module_hook23; int /*<<< orphan*/ * module_hook12; int /*<<< orphan*/ * module_hash_init_selftest; int /*<<< orphan*/ * module_deep_comp_kernel; int /*<<< orphan*/ * module_jit_cache_disable; int /*<<< orphan*/ * module_jit_build_options; int /*<<< orphan*/ * module_extra_tmp_size; int /*<<< orphan*/ * module_extra_buffer_size; int /*<<< orphan*/ * module_hash_encode_status; int /*<<< orphan*/ * module_hash_encode_potfile; int /*<<< orphan*/ * module_hash_decode_zero_hash; int /*<<< orphan*/ * module_hash_decode_potfile; int /*<<< orphan*/ * module_hash_binary_save; int /*<<< orphan*/ * module_hash_binary_parse; int /*<<< orphan*/ * module_hash_binary_count; int /*<<< orphan*/ * module_unstable_warning; int /*<<< orphan*/ * module_potfile_custom_check; int /*<<< orphan*/ * module_benchmark_salt; int /*<<< orphan*/ * module_benchmark_hook_salt; int /*<<< orphan*/ * module_benchmark_esalt; int /*<<< orphan*/  (* module_init ) (TYPE_3__*) ;} ;
typedef  TYPE_3__ module_ctx_t ;
struct TYPE_217__ {int benchmark_mask; int dictstat_disable; int esalt_size; int forced_outfile_format; int hash_mode; int hlfmt_disable; int hook_salt_size; int hook_size; int kernel_accel_min; int kernel_accel_max; int kernel_loops_min; int kernel_loops_max; int kernel_threads_min; int kernel_threads_max; int outfile_check_disable; int outfile_check_nocomp; int potfile_disable; int potfile_keep_all_hashes; int pwdump_column; int separator; int tmp_size; int warmup_disable; int attack_exec; int dgst_pos0; int dgst_pos1; int dgst_pos2; int dgst_pos3; int dgst_size; int hash_category; int hash_name; int kern_type; int opti_type; int opts_type; scalar_t__ salt_type; int st_hash; int st_pass; int has_optimized_kernel; int has_pure_kernel; int is_salted; int pw_max; int pw_min; int salt_max; int salt_min; } ;
typedef  TYPE_4__ hashconfig_t ;
struct TYPE_218__ {TYPE_2__* user_options_extra; TYPE_1__* user_options; TYPE_3__* module_ctx; TYPE_4__* hashconfig; TYPE_6__* folder_config; } ;
typedef  TYPE_5__ hashcat_ctx_t ;
struct TYPE_219__ {int /*<<< orphan*/  shared_dir; } ;
typedef  TYPE_6__ folder_config_t ;

/* Variables and functions */
 scalar_t__ MODULE_CONTEXT_SIZE_CURRENT ; 
 int MODULE_DEFAULT (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 scalar_t__ MODULE_INTERFACE_VERSION_MINIMUM ; 
 int OPTI_TYPE_APPENDED_SALT ; 
 int OPTI_TYPE_MEET_IN_MIDDLE ; 
 int OPTI_TYPE_OPTIMIZED_KERNEL ; 
 int OPTI_TYPE_PRECOMPUTE_INIT ; 
 int OPTI_TYPE_PREPENDED_SALT ; 
 int OPTS_TYPE_BINARY_HASHFILE ; 
 int OPTS_TYPE_KEYBOARD_MAPPING ; 
 int OPTS_TYPE_PT_ADD01 ; 
 int OPTS_TYPE_PT_ADD02 ; 
 int OPTS_TYPE_PT_ADD06 ; 
 int OPTS_TYPE_PT_ADD80 ; 
 int OPTS_TYPE_PT_ADDBITS14 ; 
 int OPTS_TYPE_PT_ADDBITS15 ; 
 int OPTS_TYPE_PT_NEVERCRACK ; 
 int OPTS_TYPE_PT_UTF16BE ; 
 int OPTS_TYPE_PT_UTF16LE ; 
 int OPTS_TYPE_ST_ADD01 ; 
 int OPTS_TYPE_ST_ADD02 ; 
 int OPTS_TYPE_ST_ADD80 ; 
 int OPTS_TYPE_ST_ADDBITS14 ; 
 int OPTS_TYPE_ST_ADDBITS15 ; 
 int OPTS_TYPE_ST_HEX ; 
 int OPTS_TYPE_ST_UTF16BE ; 
 int OPTS_TYPE_ST_UTF16LE ; 
 int OPTS_TYPE_SUGGEST_KG ; 
 scalar_t__ SALT_TYPE_EMBEDDED ; 
 scalar_t__ SALT_TYPE_GENERIC ; 
 scalar_t__ SALT_TYPE_VIRTUAL ; 
 int default_benchmark_mask (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_dictstat_disable (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_esalt_size (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_forced_outfile_format (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_hash_mode (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_hlfmt_disable (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_hook_salt_size (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_hook_size (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_kernel_accel_max (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_kernel_accel_min (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_kernel_loops_max (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_kernel_loops_min (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_kernel_threads_max (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_kernel_threads_min (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_outfile_check_disable (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_outfile_check_nocomp (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_potfile_disable (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_potfile_keep_all_hashes (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_pw_max (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_pw_min (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_pwdump_column (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_salt_max (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_salt_min (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_separator (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_tmp_size (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int default_warmup_disable (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  event_log_error (TYPE_5__*,char*,...) ; 
 int /*<<< orphan*/  event_log_warning (TYPE_5__*,char*,...) ; 
 int /*<<< orphan*/  generate_source_kernel_filename (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,char*) ; 
 void* hc_path_read (char*) ; 
 int module_load (TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int stub10 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub11 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub12 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 scalar_t__ stub13 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub14 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub15 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub16 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub17 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub18 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub19 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub2 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub20 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub21 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub22 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub23 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub24 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub25 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub26 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub27 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub28 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub29 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub3 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub30 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub31 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub32 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub33 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub34 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub35 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub36 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub37 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub38 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub39 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub4 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub40 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub41 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub5 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub6 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub7 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub8 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 
 int stub9 (TYPE_4__*,TYPE_1__ const*,TYPE_2__ const*) ; 

int hashconfig_init (hashcat_ctx_t *hashcat_ctx)
{
  const folder_config_t      *folder_config      = hashcat_ctx->folder_config;
        hashconfig_t         *hashconfig         = hashcat_ctx->hashconfig;
        module_ctx_t         *module_ctx         = hashcat_ctx->module_ctx;
  const user_options_t       *user_options       = hashcat_ctx->user_options;
  const user_options_extra_t *user_options_extra = hashcat_ctx->user_options_extra;

  // set some boring defaults

  hashconfig->benchmark_mask          = default_benchmark_mask          (hashconfig, user_options, user_options_extra);
  hashconfig->dictstat_disable        = default_dictstat_disable        (hashconfig, user_options, user_options_extra);
  hashconfig->esalt_size              = default_esalt_size              (hashconfig, user_options, user_options_extra);
  hashconfig->forced_outfile_format   = default_forced_outfile_format   (hashconfig, user_options, user_options_extra);
  hashconfig->hash_mode               = default_hash_mode               (hashconfig, user_options, user_options_extra);
  hashconfig->hlfmt_disable           = default_hlfmt_disable           (hashconfig, user_options, user_options_extra);
  hashconfig->hook_salt_size          = default_hook_salt_size          (hashconfig, user_options, user_options_extra);
  hashconfig->hook_size               = default_hook_size               (hashconfig, user_options, user_options_extra);
  hashconfig->kernel_accel_min        = default_kernel_accel_min        (hashconfig, user_options, user_options_extra);
  hashconfig->kernel_accel_max        = default_kernel_accel_max        (hashconfig, user_options, user_options_extra);
  hashconfig->kernel_loops_min        = default_kernel_loops_min        (hashconfig, user_options, user_options_extra);
  hashconfig->kernel_loops_max        = default_kernel_loops_max        (hashconfig, user_options, user_options_extra);
  hashconfig->kernel_threads_min      = default_kernel_threads_min      (hashconfig, user_options, user_options_extra);
  hashconfig->kernel_threads_max      = default_kernel_threads_max      (hashconfig, user_options, user_options_extra);
  hashconfig->outfile_check_disable   = default_outfile_check_disable   (hashconfig, user_options, user_options_extra);
  hashconfig->outfile_check_nocomp    = default_outfile_check_nocomp    (hashconfig, user_options, user_options_extra);
  hashconfig->potfile_disable         = default_potfile_disable         (hashconfig, user_options, user_options_extra);
  hashconfig->potfile_keep_all_hashes = default_potfile_keep_all_hashes (hashconfig, user_options, user_options_extra);
  hashconfig->pwdump_column           = default_pwdump_column           (hashconfig, user_options, user_options_extra);
  hashconfig->separator               = default_separator               (hashconfig, user_options, user_options_extra);
  hashconfig->tmp_size                = default_tmp_size                (hashconfig, user_options, user_options_extra);
  hashconfig->warmup_disable          = default_warmup_disable          (hashconfig, user_options, user_options_extra);

  // finally, the real stuff

  const bool rc_load = module_load (hashcat_ctx, module_ctx, user_options->hash_mode);

  if (rc_load == false) return -1;

  module_ctx->module_init (module_ctx);

  if (module_ctx->module_context_size != MODULE_CONTEXT_SIZE_CURRENT)
  {
    event_log_error (hashcat_ctx, "module context size is invalid. Old template?");

    return -1;
  }

  if (module_ctx->module_interface_version < MODULE_INTERFACE_VERSION_MINIMUM)
  {
    event_log_error (hashcat_ctx, "module interface version is outdated, please compile");

    return -1;
  }

  // check for missing pointer assignements

  #define CHECK_DEFINED(func)                                                     \
    if (func == NULL)                                                             \
    {                                                                             \
      event_log_error (hashcat_ctx, "Missing symbol definitions. Old template?"); \
                                                                                  \
      return -1;                                                                  \
    }

  CHECK_DEFINED (module_ctx->module_attack_exec);
  CHECK_DEFINED (module_ctx->module_benchmark_esalt);
  CHECK_DEFINED (module_ctx->module_benchmark_hook_salt);
  CHECK_DEFINED (module_ctx->module_benchmark_mask);
  CHECK_DEFINED (module_ctx->module_benchmark_salt);
  CHECK_DEFINED (module_ctx->module_dictstat_disable);
  CHECK_DEFINED (module_ctx->module_dgst_pos0);
  CHECK_DEFINED (module_ctx->module_dgst_pos1);
  CHECK_DEFINED (module_ctx->module_dgst_pos2);
  CHECK_DEFINED (module_ctx->module_dgst_pos3);
  CHECK_DEFINED (module_ctx->module_dgst_size);
  CHECK_DEFINED (module_ctx->module_esalt_size);
  CHECK_DEFINED (module_ctx->module_forced_outfile_format);
  CHECK_DEFINED (module_ctx->module_hash_category);
  CHECK_DEFINED (module_ctx->module_hash_name);
  CHECK_DEFINED (module_ctx->module_hash_mode);
  CHECK_DEFINED (module_ctx->module_hlfmt_disable);
  CHECK_DEFINED (module_ctx->module_hook_salt_size);
  CHECK_DEFINED (module_ctx->module_hook_size);
  CHECK_DEFINED (module_ctx->module_kernel_accel_min);
  CHECK_DEFINED (module_ctx->module_kernel_accel_max);
  CHECK_DEFINED (module_ctx->module_kernel_loops_min);
  CHECK_DEFINED (module_ctx->module_kernel_loops_max);
  CHECK_DEFINED (module_ctx->module_kernel_threads_min);
  CHECK_DEFINED (module_ctx->module_kernel_threads_max);
  CHECK_DEFINED (module_ctx->module_kern_type);
  CHECK_DEFINED (module_ctx->module_kern_type_dynamic);
  CHECK_DEFINED (module_ctx->module_opti_type);
  CHECK_DEFINED (module_ctx->module_opts_type);
  CHECK_DEFINED (module_ctx->module_outfile_check_disable);
  CHECK_DEFINED (module_ctx->module_outfile_check_nocomp);
  CHECK_DEFINED (module_ctx->module_potfile_custom_check);
  CHECK_DEFINED (module_ctx->module_potfile_disable);
  CHECK_DEFINED (module_ctx->module_potfile_keep_all_hashes);
  CHECK_DEFINED (module_ctx->module_pwdump_column);
  CHECK_DEFINED (module_ctx->module_pw_min);
  CHECK_DEFINED (module_ctx->module_pw_max);
  CHECK_DEFINED (module_ctx->module_salt_min);
  CHECK_DEFINED (module_ctx->module_salt_max);
  CHECK_DEFINED (module_ctx->module_salt_type);
  CHECK_DEFINED (module_ctx->module_separator);
  CHECK_DEFINED (module_ctx->module_st_hash);
  CHECK_DEFINED (module_ctx->module_st_pass);
  CHECK_DEFINED (module_ctx->module_tmp_size);
  CHECK_DEFINED (module_ctx->module_unstable_warning);
  CHECK_DEFINED (module_ctx->module_warmup_disable);
  CHECK_DEFINED (module_ctx->module_hash_binary_count);
  CHECK_DEFINED (module_ctx->module_hash_binary_parse);
  CHECK_DEFINED (module_ctx->module_hash_binary_save);
  CHECK_DEFINED (module_ctx->module_hash_decode_potfile);
  CHECK_DEFINED (module_ctx->module_hash_decode_zero_hash);
  CHECK_DEFINED (module_ctx->module_hash_decode);
  CHECK_DEFINED (module_ctx->module_hash_encode_potfile);
  CHECK_DEFINED (module_ctx->module_hash_encode_status);
  CHECK_DEFINED (module_ctx->module_hash_encode);
  CHECK_DEFINED (module_ctx->module_extra_buffer_size);
  CHECK_DEFINED (module_ctx->module_extra_tmp_size);
  CHECK_DEFINED (module_ctx->module_jit_build_options);
  CHECK_DEFINED (module_ctx->module_jit_cache_disable);
  CHECK_DEFINED (module_ctx->module_deep_comp_kernel);
  CHECK_DEFINED (module_ctx->module_hash_init_selftest);
  CHECK_DEFINED (module_ctx->module_hook12);
  CHECK_DEFINED (module_ctx->module_hook23);
  CHECK_DEFINED (module_ctx->module_build_plain_postprocess);

  #undef CHECK_DEFINED

  // mandatory functions check

  #define CHECK_MANDATORY(func)                                               \
    if (func == MODULE_DEFAULT)                                               \
    {                                                                         \
      event_log_error (hashcat_ctx, "Missing mandatory symbol definitions");  \
                                                                              \
      return -1;                                                              \
    }

  CHECK_MANDATORY (module_ctx->module_attack_exec);
  CHECK_MANDATORY (module_ctx->module_dgst_pos0);
  CHECK_MANDATORY (module_ctx->module_dgst_pos1);
  CHECK_MANDATORY (module_ctx->module_dgst_pos2);
  CHECK_MANDATORY (module_ctx->module_dgst_pos3);
  CHECK_MANDATORY (module_ctx->module_dgst_size);
  CHECK_MANDATORY (module_ctx->module_hash_decode);
  // CHECK_MANDATORY (module_ctx->module_hash_encode); we do that one later
  CHECK_MANDATORY (module_ctx->module_hash_category);
  CHECK_MANDATORY (module_ctx->module_hash_name);
  CHECK_MANDATORY (module_ctx->module_kern_type);
  CHECK_MANDATORY (module_ctx->module_opti_type);
  CHECK_MANDATORY (module_ctx->module_opts_type);
  CHECK_MANDATORY (module_ctx->module_salt_type);
  CHECK_MANDATORY (module_ctx->module_st_hash);
  CHECK_MANDATORY (module_ctx->module_st_pass);

  hashconfig->attack_exec   = module_ctx->module_attack_exec    (hashconfig, user_options, user_options_extra);
  hashconfig->dgst_pos0     = module_ctx->module_dgst_pos0      (hashconfig, user_options, user_options_extra);
  hashconfig->dgst_pos1     = module_ctx->module_dgst_pos1      (hashconfig, user_options, user_options_extra);
  hashconfig->dgst_pos2     = module_ctx->module_dgst_pos2      (hashconfig, user_options, user_options_extra);
  hashconfig->dgst_pos3     = module_ctx->module_dgst_pos3      (hashconfig, user_options, user_options_extra);
  hashconfig->dgst_size     = module_ctx->module_dgst_size      (hashconfig, user_options, user_options_extra);
  hashconfig->hash_category = module_ctx->module_hash_category  (hashconfig, user_options, user_options_extra);
  hashconfig->hash_name     = module_ctx->module_hash_name      (hashconfig, user_options, user_options_extra);
  hashconfig->kern_type     = module_ctx->module_kern_type      (hashconfig, user_options, user_options_extra);
  hashconfig->opti_type     = module_ctx->module_opti_type      (hashconfig, user_options, user_options_extra);
  hashconfig->opts_type     = module_ctx->module_opts_type      (hashconfig, user_options, user_options_extra);
  hashconfig->salt_type     = module_ctx->module_salt_type      (hashconfig, user_options, user_options_extra);
  hashconfig->st_hash       = module_ctx->module_st_hash        (hashconfig, user_options, user_options_extra);
  hashconfig->st_pass       = module_ctx->module_st_pass        (hashconfig, user_options, user_options_extra);

  if ((hashconfig->opts_type & OPTS_TYPE_BINARY_HASHFILE) == 0)
  {
    CHECK_MANDATORY (module_ctx->module_hash_encode);
  }

  #undef CHECK_MANDATORY

  if (module_ctx->module_benchmark_mask           != MODULE_DEFAULT) hashconfig->benchmark_mask          = module_ctx->module_benchmark_mask           (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_dictstat_disable         != MODULE_DEFAULT) hashconfig->dictstat_disable        = module_ctx->module_dictstat_disable         (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_esalt_size               != MODULE_DEFAULT) hashconfig->esalt_size              = module_ctx->module_esalt_size               (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_forced_outfile_format    != MODULE_DEFAULT) hashconfig->forced_outfile_format   = module_ctx->module_forced_outfile_format    (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_hash_mode                != MODULE_DEFAULT) hashconfig->hash_mode               = module_ctx->module_hash_mode                (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_hlfmt_disable            != MODULE_DEFAULT) hashconfig->hlfmt_disable           = module_ctx->module_hlfmt_disable            (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_hook_salt_size           != MODULE_DEFAULT) hashconfig->hook_salt_size          = module_ctx->module_hook_salt_size           (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_hook_size                != MODULE_DEFAULT) hashconfig->hook_size               = module_ctx->module_hook_size                (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_kernel_accel_min         != MODULE_DEFAULT) hashconfig->kernel_accel_min        = module_ctx->module_kernel_accel_min         (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_kernel_accel_max         != MODULE_DEFAULT) hashconfig->kernel_accel_max        = module_ctx->module_kernel_accel_max         (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_kernel_loops_min         != MODULE_DEFAULT) hashconfig->kernel_loops_min        = module_ctx->module_kernel_loops_min         (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_kernel_loops_max         != MODULE_DEFAULT) hashconfig->kernel_loops_max        = module_ctx->module_kernel_loops_max         (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_kernel_threads_min       != MODULE_DEFAULT) hashconfig->kernel_threads_min      = module_ctx->module_kernel_threads_min       (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_kernel_threads_max       != MODULE_DEFAULT) hashconfig->kernel_threads_max      = module_ctx->module_kernel_threads_max       (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_outfile_check_disable    != MODULE_DEFAULT) hashconfig->outfile_check_disable   = module_ctx->module_outfile_check_disable    (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_outfile_check_nocomp     != MODULE_DEFAULT) hashconfig->outfile_check_nocomp    = module_ctx->module_outfile_check_nocomp     (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_potfile_disable          != MODULE_DEFAULT) hashconfig->potfile_disable         = module_ctx->module_potfile_disable          (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_potfile_keep_all_hashes  != MODULE_DEFAULT) hashconfig->potfile_keep_all_hashes = module_ctx->module_potfile_keep_all_hashes  (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_pwdump_column            != MODULE_DEFAULT) hashconfig->pwdump_column           = module_ctx->module_pwdump_column            (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_separator                != MODULE_DEFAULT) hashconfig->separator               = module_ctx->module_separator                (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_tmp_size                 != MODULE_DEFAULT) hashconfig->tmp_size                = module_ctx->module_tmp_size                 (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_warmup_disable           != MODULE_DEFAULT) hashconfig->warmup_disable          = module_ctx->module_warmup_disable           (hashconfig, user_options, user_options_extra);

  if (user_options->keyboard_layout_mapping)
  {
    if ((hashconfig->opts_type & OPTS_TYPE_KEYBOARD_MAPPING) == 0)
    {
      event_log_error (hashcat_ctx, "Parameter --keyboard-layout-mapping not valid for hash-type %u", hashconfig->hash_mode);

      return -1;
    }
  }

  if (user_options->hex_salt)
  {
    if (hashconfig->salt_type == SALT_TYPE_GENERIC)
    {
      hashconfig->opts_type |= OPTS_TYPE_ST_HEX;
    }
    else
    {
      event_log_error (hashcat_ctx, "Parameter --hex-salt not valid for hash-type %u", hashconfig->hash_mode);

      return -1;
    }
  }

  if (user_options->keep_guessing)
  {
    hashconfig->opts_type |= OPTS_TYPE_PT_NEVERCRACK;
  }
  else
  {
    if (hashconfig->opti_type & OPTS_TYPE_SUGGEST_KG)
    {
      if (user_options->quiet == false)
      {
        event_log_warning (hashcat_ctx, "This hash-mode is known to emit multiple valid password candidates for the same hash.");
        event_log_warning (hashcat_ctx, "Use --keep-guessing to prevent hashcat from shutdown after the hash has been cracked.");
        event_log_warning (hashcat_ctx, NULL);
      }
    }
  }

  hashconfig->has_optimized_kernel  = false;
  hashconfig->has_pure_kernel       = false;

  if (module_ctx->module_kern_type_dynamic != MODULE_DEFAULT)
  {
    // some hash modes tell hashcat about their exact hash-mode inside the parser (eg. luks and jwt)
  }
  else
  {
    // some kernels do not have an optimized kernel, simply because they do not need them
    // or because they are not yet converted, for them we should switch off optimized mode

    char source_file[256] = { 0 };

    generate_source_kernel_filename (user_options->slow_candidates, hashconfig->attack_exec, user_options_extra->attack_kern, hashconfig->kern_type, false, folder_config->shared_dir, source_file);

    hashconfig->has_pure_kernel = hc_path_read (source_file);

    generate_source_kernel_filename (user_options->slow_candidates, hashconfig->attack_exec, user_options_extra->attack_kern, hashconfig->kern_type, true, folder_config->shared_dir, source_file);

    hashconfig->has_optimized_kernel = hc_path_read (source_file);

    if (user_options->example_hashes == false)
    {
      if (user_options->optimized_kernel_enable == true)
      {
        if (hashconfig->has_optimized_kernel == false)
        {
          if (user_options->quiet == false) event_log_warning (hashcat_ctx, "%s: Optimized OpenCL kernel requested but not needed - falling back to pure OpenCL kernel", source_file);
        }
        else
        {
          hashconfig->opti_type |= OPTI_TYPE_OPTIMIZED_KERNEL;
        }
      }
      else
      {
        if (hashconfig->has_pure_kernel == false)
        {
          if (user_options->quiet == false) event_log_warning (hashcat_ctx, "%s: Pure OpenCL kernel not found, falling back to optimized OpenCL kernel", source_file);

          hashconfig->opti_type |= OPTI_TYPE_OPTIMIZED_KERNEL;
        }
        else
        {
          // nothing to do
        }
      }
    }
  }

  if ((hashconfig->opti_type & OPTI_TYPE_OPTIMIZED_KERNEL) == 0)
  {
    hashconfig->opts_type &= ~OPTS_TYPE_PT_UTF16LE;
    hashconfig->opts_type &= ~OPTS_TYPE_PT_UTF16BE;
    hashconfig->opts_type &= ~OPTS_TYPE_PT_ADD01;
    hashconfig->opts_type &= ~OPTS_TYPE_PT_ADD02;
    hashconfig->opts_type &= ~OPTS_TYPE_PT_ADD06;
    hashconfig->opts_type &= ~OPTS_TYPE_PT_ADD80;
    hashconfig->opts_type &= ~OPTS_TYPE_PT_ADDBITS14;
    hashconfig->opts_type &= ~OPTS_TYPE_PT_ADDBITS15;
    hashconfig->opts_type &= ~OPTS_TYPE_ST_UTF16LE;
    hashconfig->opts_type &= ~OPTS_TYPE_ST_UTF16BE;
    hashconfig->opts_type &= ~OPTS_TYPE_ST_ADD01;
    hashconfig->opts_type &= ~OPTS_TYPE_ST_ADD02;
    hashconfig->opts_type &= ~OPTS_TYPE_ST_ADD80;
    hashconfig->opts_type &= ~OPTS_TYPE_ST_ADDBITS14;
    hashconfig->opts_type &= ~OPTS_TYPE_ST_ADDBITS15;

    hashconfig->opti_type &= ~OPTI_TYPE_PRECOMPUTE_INIT;
    hashconfig->opti_type &= ~OPTI_TYPE_MEET_IN_MIDDLE;
    hashconfig->opti_type &= ~OPTI_TYPE_PREPENDED_SALT;
    hashconfig->opti_type &= ~OPTI_TYPE_APPENDED_SALT;
  }

  const bool is_salted = ((hashconfig->salt_type == SALT_TYPE_GENERIC)
                       |  (hashconfig->salt_type == SALT_TYPE_EMBEDDED)
                       |  (hashconfig->salt_type == SALT_TYPE_VIRTUAL));

  hashconfig->is_salted = is_salted;

  // those depend on some previously defined values

  hashconfig->pw_max    = default_pw_max    (hashconfig, user_options, user_options_extra);
  hashconfig->pw_min    = default_pw_min    (hashconfig, user_options, user_options_extra);
  hashconfig->salt_max  = default_salt_max  (hashconfig, user_options, user_options_extra);
  hashconfig->salt_min  = default_salt_min  (hashconfig, user_options, user_options_extra);

  if (module_ctx->module_pw_max   != MODULE_DEFAULT) hashconfig->pw_max    = module_ctx->module_pw_max   (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_pw_min   != MODULE_DEFAULT) hashconfig->pw_min    = module_ctx->module_pw_min   (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_salt_max != MODULE_DEFAULT) hashconfig->salt_max  = module_ctx->module_salt_max (hashconfig, user_options, user_options_extra);
  if (module_ctx->module_salt_min != MODULE_DEFAULT) hashconfig->salt_min  = module_ctx->module_salt_min (hashconfig, user_options, user_options_extra);

  return 0;
}