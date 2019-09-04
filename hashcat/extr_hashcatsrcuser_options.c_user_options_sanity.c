#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int hc_argc; int slow_candidates; scalar_t__ attack_mode; int hccapx_message_pair_chgd; int remove; int hccapx_message_pair; int limit_chgd; scalar_t__ limit; int runtime_chgd; scalar_t__ runtime; int loopback; scalar_t__ hash_mode; int outfile_format; int left; int outfile_format_chgd; int show; scalar_t__ increment_min; scalar_t__ increment_max; scalar_t__ veracrypt_pim_start; scalar_t__ veracrypt_pim_stop; int increment; int progress_only; int speed_only; int increment_min_chgd; int increment_max_chgd; scalar_t__ rp_files_cnt; scalar_t__ rp_gen; scalar_t__ bitmap_min; scalar_t__ bitmap_max; scalar_t__ rp_gen_func_min; scalar_t__ rp_gen_func_max; int kernel_accel_chgd; int force; int kernel_accel; int kernel_loops_chgd; int kernel_loops; int kernel_threads_chgd; int kernel_threads; int workload_profile; int opencl_vector_width_chgd; int opencl_vector_width; int potfile_disable; int outfile_autohex; int keyspace; int machine_readable; int status_json; int remove_timer_chgd; int remove_timer; int debug_mode; int spin_damp; int spin_damp_chgd; int benchmark; int attack_mode_chgd; int stdin_timeout_abort_chgd; int stdout_flag; int version; int usage; int example_hashes; int opencl_info; int restore; int /*<<< orphan*/  hc_bin; int /*<<< orphan*/ * custom_charset_4; int /*<<< orphan*/ * custom_charset_3; int /*<<< orphan*/ * custom_charset_2; int /*<<< orphan*/ * custom_charset_1; int /*<<< orphan*/ * opencl_device_types; int /*<<< orphan*/ * opencl_devices; int /*<<< orphan*/ * opencl_platforms; int /*<<< orphan*/ * cpu_affinity; int /*<<< orphan*/ * session; int /*<<< orphan*/ * debug_file; int /*<<< orphan*/ * outfile; int /*<<< orphan*/ * restore_file_path; int /*<<< orphan*/ * markov_hcstat2; int /*<<< orphan*/ * induction_dir; int /*<<< orphan*/ * hc_argv; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_7__ {TYPE_1__* user_options; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 scalar_t__ ATTACK_MODE_BF ; 
 scalar_t__ ATTACK_MODE_COMBI ; 
 scalar_t__ ATTACK_MODE_HYBRID1 ; 
 scalar_t__ ATTACK_MODE_HYBRID2 ; 
 scalar_t__ ATTACK_MODE_NONE ; 
 scalar_t__ ATTACK_MODE_STRAIGHT ; 
 scalar_t__ INCREMENT_MAX ; 
 scalar_t__ INCREMENT_MIN ; 
 scalar_t__ MODULE_HASH_MODES_MAXIMUM ; 
 int /*<<< orphan*/  event_log_error (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  event_log_warning (TYPE_2__*,char*) ; 
 int is_power_of_2 (int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage_mini_print (int /*<<< orphan*/ ) ; 

int user_options_sanity (hashcat_ctx_t *hashcat_ctx)
{
  user_options_t *user_options = hashcat_ctx->user_options;

  if (user_options->hc_argc < 0)
  {
    event_log_error (hashcat_ctx, "hc_argc %d is invalid.", user_options->hc_argc);

    return -1;
  }

  if (user_options->hc_argv == NULL)
  {
    event_log_error (hashcat_ctx, "hc_argv is NULL.");

    return -1;
  }

  #ifdef WITH_BRAIN
  if ((user_options->brain_client == true) && (user_options->brain_server == true))
  {
    event_log_error (hashcat_ctx, "Can not have --brain-client and --brain-server at the same time");

    return -1;
  }

  if ((user_options->brain_client_features < 1) || (user_options->brain_client_features > 3))
  {
    event_log_error (hashcat_ctx, "Invalid --brain-client-feature argument");

    return -1;
  }

  if ((user_options->brain_client == true) && (user_options->brain_password_chgd == false))
  {
    event_log_error (hashcat_ctx, "Brain clients need to set --brain-password");

    return -1;
  }
  #endif

  if (user_options->slow_candidates == true)
  {
    if ((user_options->attack_mode != ATTACK_MODE_STRAIGHT)
     && (user_options->attack_mode != ATTACK_MODE_COMBI)
     && (user_options->attack_mode != ATTACK_MODE_BF))
    {
      event_log_error (hashcat_ctx, "Invalid attack mode (-a) value specified in slow-candidates mode.");

      return -1;
    }
  }
  #ifdef WITH_BRAIN
  else if (user_options->brain_client == true)
  {
    if ((user_options->attack_mode != ATTACK_MODE_STRAIGHT)
     && (user_options->attack_mode != ATTACK_MODE_COMBI)
     && (user_options->attack_mode != ATTACK_MODE_BF))
    {
      event_log_error (hashcat_ctx, "Invalid attack mode (-a) value specified in brain-client mode.");

      return -1;
    }
  }
  #endif
  else
  {
    if ((user_options->attack_mode != ATTACK_MODE_STRAIGHT)
     && (user_options->attack_mode != ATTACK_MODE_COMBI)
     && (user_options->attack_mode != ATTACK_MODE_BF)
     && (user_options->attack_mode != ATTACK_MODE_HYBRID1)
     && (user_options->attack_mode != ATTACK_MODE_HYBRID2)
     && (user_options->attack_mode != ATTACK_MODE_NONE))
    {
      event_log_error (hashcat_ctx, "Invalid attack mode (-a) value specified.");

      return -1;
    }
  }

  if (user_options->hccapx_message_pair_chgd == true)
  {
    if (user_options->remove == true)
    {
      event_log_error (hashcat_ctx, "Combining --remove with --hccapx-message-pair is not allowed.");

      return -1;
    }

    if (user_options->hccapx_message_pair >= 6)
    {
      event_log_error (hashcat_ctx, "Invalid --hccapx-message-pair value specified.");

      return -1;
    }
  }

  /*
  if (user_options->skip_chgd == true && user_options->skip == 0)
  {
    event_log_error (hashcat_ctx, "Invalid --skip value specified.");

    return -1;
  }
  */

  if (user_options->limit_chgd == true && user_options->limit == 0)
  {
    event_log_error (hashcat_ctx, "Invalid --limit value specified.");

    return -1;
  }

  if (user_options->runtime_chgd == true && user_options->runtime == 0)
  {
    event_log_error (hashcat_ctx, "Invalid --runtime value specified.");

    return -1;
  }

  if (user_options->runtime_chgd == true && user_options->loopback == true)
  {
    event_log_error (hashcat_ctx, "Combining --limit with --loopback is not allowed.");

    return -1;
  }

  if (user_options->hash_mode >= MODULE_HASH_MODES_MAXIMUM)
  {
    event_log_error (hashcat_ctx, "Invalid -m (hash type) value specified.");

    return -1;
  }

  if (user_options->outfile_format > 16)
  {
    event_log_error (hashcat_ctx, "Invalid --outfile-format value specified.");

    return -1;
  }

  if (user_options->left == true)
  {
    if (user_options->outfile_format_chgd == true)
    {
      if (user_options->outfile_format > 1)
      {
        event_log_error (hashcat_ctx, "Combining --outfile-format > 1 with --left is not allowed.");

        return -1;
      }
    }
  }

  if (user_options->show == true)
  {
    if (user_options->outfile_format_chgd == true)
    {
      if (user_options->outfile_format > 7)
      {
        event_log_error (hashcat_ctx, "Combining --outfile-format > 7 with --show is not allowed.");

        return -1;
      }
    }
  }

  if (user_options->increment_min < INCREMENT_MIN)
  {
    event_log_error (hashcat_ctx, "Invalid --increment-min value specified.");

    return -1;
  }

  if (user_options->increment_max > INCREMENT_MAX)
  {
    event_log_error (hashcat_ctx, "Invalid --increment-max value specified.");

    return -1;
  }

  if ((user_options->veracrypt_pim_start != 0) && (user_options->veracrypt_pim_stop == 0))
  {
    event_log_error (hashcat_ctx, "If --veracrypt-pim-start is specified then --veracrypt-pim-stop needs to be specified, too.");

    return -1;
  }

  if ((user_options->veracrypt_pim_start == 0) && (user_options->veracrypt_pim_stop != 0))
  {
    event_log_error (hashcat_ctx, "If --veracrypt-pim-stop is specified then --veracrypt-pim-start needs to be specified, too.");

    return -1;
  }

  if (user_options->veracrypt_pim_start > user_options->veracrypt_pim_stop)
  {
    event_log_error (hashcat_ctx, "Invalid --veracrypt-pim-start value specified.");

    return -1;
  }

  if (user_options->increment_min > user_options->increment_max)
  {
    event_log_error (hashcat_ctx, "Invalid --increment-min value specified - must be >= --increment-max.");

    return -1;
  }

  if ((user_options->increment == true) && (user_options->progress_only == true))
  {
    event_log_error (hashcat_ctx, "Increment is not allowed in combination with --progress-only.");

    return -1;
  }

  if ((user_options->increment == true) && (user_options->speed_only == true))
  {
    event_log_error (hashcat_ctx, "Increment is not allowed in combination with --speed-only.");

    return -1;
  }

  if ((user_options->increment == true) && (user_options->attack_mode == ATTACK_MODE_STRAIGHT))
  {
    event_log_error (hashcat_ctx, "Increment is not allowed in attack mode 0 (straight).");

    return -1;
  }

  if ((user_options->increment == false) && (user_options->increment_min_chgd == true))
  {
    event_log_error (hashcat_ctx, "Increment-min is only supported when combined with -i/--increment.");

    return -1;
  }

  if ((user_options->increment == false) && (user_options->increment_max_chgd == true))
  {
    event_log_error (hashcat_ctx, "Increment-max is only supported combined with -i/--increment.");

    return -1;
  }

  if ((user_options->rp_files_cnt > 0) && (user_options->rp_gen > 0))
  {
    event_log_error (hashcat_ctx, "Combining -r/--rules-file and -g/--rules-generate is not supported.");

    return -1;
  }

  if ((user_options->rp_files_cnt > 0) || (user_options->rp_gen > 0))
  {
    if (user_options->attack_mode != ATTACK_MODE_STRAIGHT)
    {
      event_log_error (hashcat_ctx, "Use of -r/--rules-file and -g/--rules-generate only allowed in attack mode 0.");

      return -1;
    }
  }

  if (user_options->bitmap_min > user_options->bitmap_max)
  {
    event_log_error (hashcat_ctx, "Invalid --bitmap-min value specified.");

    return -1;
  }

  if (user_options->rp_gen_func_min > user_options->rp_gen_func_max)
  {
    event_log_error (hashcat_ctx, "Invalid --rp-gen-func-min value specified.");

    return -1;
  }

  if (user_options->kernel_accel_chgd == true)
  {
    if (user_options->force == false)
    {
      event_log_error (hashcat_ctx, "The manual use of the -n option (or --kernel-accel) is outdated.");

      event_log_warning (hashcat_ctx, "Please consider using the -w option instead.");
      event_log_warning (hashcat_ctx, "You can use --force to override this, but do not report related errors.");
      event_log_warning (hashcat_ctx, NULL);

      return -1;
    }

    if (user_options->kernel_accel < 1)
    {
      event_log_error (hashcat_ctx, "Invalid --kernel-accel value specified - must be greater than 0.");

      return -1;
    }

    if (user_options->kernel_accel > 1024)
    {
      event_log_error (hashcat_ctx, "Invalid --kernel-accel value specified - must be <= 1024.");

      return -1;
    }
  }

  if (user_options->kernel_loops_chgd == true)
  {
    if (user_options->force == false)
    {
      event_log_error (hashcat_ctx, "The manual use of the -u option (or --kernel-loops) is outdated.");

      event_log_warning (hashcat_ctx, "Please consider using the -w option instead.");
      event_log_warning (hashcat_ctx, "You can use --force to override this, but do not report related errors.");
      event_log_warning (hashcat_ctx, NULL);

      return -1;
    }

    if (user_options->kernel_loops < 1)
    {
      event_log_error (hashcat_ctx, "Invalid kernel-loops specified.");

      return -1;
    }

    if (user_options->kernel_loops > 1024)
    {
      event_log_error (hashcat_ctx, "Invalid kernel-loops specified.");

      return -1;
    }
  }

  if (user_options->kernel_threads_chgd == true)
  {
    if (user_options->force == false)
    {
      event_log_error (hashcat_ctx, "The manual use of the -T option (or --kernel-threads) is outdated.");

      event_log_warning (hashcat_ctx, "You can use --force to override this, but do not report related errors.");
      event_log_warning (hashcat_ctx, NULL);

      return -1;
    }

    if (user_options->kernel_threads < 1)
    {
      event_log_error (hashcat_ctx, "Invalid kernel-threads specified.");

      return -1;
    }

    if (user_options->kernel_threads > 1024)
    {
      event_log_error (hashcat_ctx, "Invalid kernel-threads specified.");

      return -1;
    }
  }

  if ((user_options->workload_profile < 1) || (user_options->workload_profile > 4))
  {
    event_log_error (hashcat_ctx, "workload-profile %u is not available.", user_options->workload_profile);

    return -1;
  }

  if (user_options->opencl_vector_width_chgd == true)
  {
    if (is_power_of_2 (user_options->opencl_vector_width) == false || user_options->opencl_vector_width > 16)
    {
      event_log_error (hashcat_ctx, "opencl-vector-width %u is not allowed.", user_options->opencl_vector_width);

      return -1;
    }
  }

  if (user_options->show == true || user_options->left == true)
  {
    if (user_options->remove == true)
    {
      event_log_error (hashcat_ctx, "Mixing --remove not allowed with --show or --left.");

      return -1;
    }

    if (user_options->potfile_disable == true)
    {
      event_log_error (hashcat_ctx, "Mixing --potfile-disable is not allowed with --show or --left.");

      return -1;
    }
  }

  if (user_options->show == true)
  {
    if (user_options->outfile_autohex == false)
    {
      event_log_error (hashcat_ctx, "Mixing --outfile-autohex-disable is not allowed with --show.");

      return -1;
    }
  }

  if (user_options->keyspace == true)
  {
    if (user_options->show == true)
    {
      event_log_error (hashcat_ctx, "Combining --show with --keyspace is not allowed.");

      return -1;
    }

   if (user_options->left == true)
    {
      event_log_error (hashcat_ctx, "Combining --left with --keyspace is not allowed.");

      return -1;
    }
  }

  if (user_options->machine_readable == true)
  {
    if (user_options->status_json == true)
    {
      event_log_error (hashcat_ctx, "The --status-json flag can not be used with --machine-readable.");

      return -1;
    }
  }

  if (user_options->remove_timer_chgd == true)
  {
    if (user_options->remove == false)
    {
      event_log_error (hashcat_ctx, "The --remove-timer flag requires --remove.");

      return -1;
    }

    if (user_options->remove_timer < 1)
    {
      event_log_error (hashcat_ctx, "The --remove-timer parameter must have a value greater than or equal to 1.");

      return -1;
    }
  }

  if (user_options->loopback == true)
  {
    if (user_options->attack_mode == ATTACK_MODE_STRAIGHT)
    {
      if ((user_options->rp_files_cnt == 0) && (user_options->rp_gen == 0))
      {
        event_log_error (hashcat_ctx, "Parameter --loopback not allowed without -r/--rules-file or -g/--rules-generate.");

        return -1;
      }
    }
    else
    {
      event_log_error (hashcat_ctx, "Parameter --loopback is only allowed in attack mode 0 (straight).");

      return -1;
    }
  }

  if (user_options->debug_mode > 0)
  {
    if (user_options->attack_mode != ATTACK_MODE_STRAIGHT)
    {
      event_log_error (hashcat_ctx, "Parameter --debug-mode option is only allowed in attack mode 0 (straight).");

      return -1;
    }

    if ((user_options->rp_files_cnt == 0) && (user_options->rp_gen == 0))
    {
      event_log_error (hashcat_ctx, "Use of --debug-mode requires -r/--rules-file or -g/--rules-generate.");

      return -1;
    }
  }

  if (user_options->debug_mode > 4)
  {
    event_log_error (hashcat_ctx, "Invalid --debug-mode value specified.");

    return -1;
  }

  if (user_options->debug_file != NULL)
  {
    if (user_options->debug_mode < 1)
    {
      event_log_error (hashcat_ctx, "Parameter --debug-file requires --debug-mode.");

      return -1;
    }
  }

  if (user_options->induction_dir != NULL)
  {
    if (user_options->attack_mode == ATTACK_MODE_BF)
    {
      event_log_error (hashcat_ctx, "Use of --induction-dir is not allowed in attack mode 3 (brute-force).");

      return -1;
    }
  }

  if (user_options->spin_damp > 100)
  {
    event_log_error (hashcat_ctx, "Values of --spin-damp must be between 0 and 100 (inclusive).");

    return -1;
  }

  if ((user_options->spin_damp_chgd == true) && (user_options->benchmark == true))
  {
    event_log_error (hashcat_ctx, "Values of --spin-damp cannot be used in combination with --benchmark.");

    return -1;
  }

  if (user_options->benchmark == true)
  {
    if (user_options->attack_mode_chgd == true)
    {
      if (user_options->attack_mode != ATTACK_MODE_BF)
      {
        event_log_error (hashcat_ctx, "Benchmark mode is only allowed in attack mode 3 (brute-force).");

        return -1;
      }
    }
  }

  if (user_options->markov_hcstat2 != NULL)
  {
    if (strlen (user_options->markov_hcstat2) == 0)
    {
      event_log_error (hashcat_ctx, "Invalid --markov-hcstat2 value - must not be empty.");

      return -1;
    }
  }

  if (user_options->restore_file_path != NULL)
  {
    if (strlen (user_options->restore_file_path) == 0)
    {
      event_log_error (hashcat_ctx, "Invalid --restore-file-path value - must not be empty.");

      return -1;
    }
  }

  if (user_options->outfile != NULL)
  {
    if (strlen (user_options->outfile) == 0)
    {
      event_log_error (hashcat_ctx, "Invalid --outfile value - must not be empty.");

      return -1;
    }
  }

  if (user_options->debug_file != NULL)
  {
    if (strlen (user_options->debug_file) == 0)
    {
      event_log_error (hashcat_ctx, "Invalid --debug-file value - must not be empty.");

      return -1;
    }
  }

  if (user_options->session != NULL)
  {
    if (strlen (user_options->session) == 0)
    {
      event_log_error (hashcat_ctx, "Invalid --session value - must not be empty.");

      return -1;
    }
  }

  if (user_options->cpu_affinity != NULL)
  {
    if (strlen (user_options->cpu_affinity) == 0)
    {
      event_log_error (hashcat_ctx, "Invalid --cpu-affinity value - must not be empty.");

      return -1;
    }
  }

  if (user_options->opencl_platforms != NULL)
  {
    if (strlen (user_options->opencl_platforms) == 0)
    {
      event_log_error (hashcat_ctx, "Invalid --opencl-platforms value - must not be empty.");

      return -1;
    }
  }

  if (user_options->opencl_devices != NULL)
  {
    if (strlen (user_options->opencl_devices) == 0)
    {
      event_log_error (hashcat_ctx, "Invalid --opencl-devices value - must not be empty.");

      return -1;
    }
  }

  if (user_options->opencl_device_types != NULL)
  {
    if (strlen (user_options->opencl_device_types) == 0)
    {
      event_log_error (hashcat_ctx, "Invalid --opencl-device-types value - must not be empty.");

      return -1;
    }
  }

  if (user_options->stdin_timeout_abort_chgd == true)
  {
    if (user_options->attack_mode != ATTACK_MODE_STRAIGHT)
    {
      event_log_error (hashcat_ctx, "Use of --stdin-timeout-abort is only allowed in attack mode 0 (straight).");

      return -1;
    }

    // --stdin-timeout-abort can only be used in stdin mode

    if (user_options->hc_argc != 1)
    {
      event_log_error (hashcat_ctx, "Use of --stdin-timeout-abort is only allowed in stdin mode (pipe).");

      return -1;
    }
  }

  #ifdef WITH_BRAIN
  if ((user_options->brain_client == true) && (user_options->remove == true))
  {
    event_log_error (hashcat_ctx, "Using --remove is not allowed if --brain-client is used.");

    return -1;
  }

  if ((user_options->brain_client == true) && (user_options->potfile_disable == true))
  {
    event_log_error (hashcat_ctx, "Using --potfile-disable is not allowed if --brain-client is used.");

    return -1;
  }
  #endif

  // custom charset checks

  if ((user_options->custom_charset_1 != NULL)
   || (user_options->custom_charset_2 != NULL)
   || (user_options->custom_charset_3 != NULL)
   || (user_options->custom_charset_4 != NULL))
  {
    if (user_options->attack_mode == ATTACK_MODE_STRAIGHT)
    {
      event_log_error (hashcat_ctx, "Custom charsets are not supported in attack mode 0 (straight).");

      return -1;
    }

    if (user_options->attack_mode == ATTACK_MODE_COMBI)
    {
      event_log_error (hashcat_ctx, "Custom charsets are not supported in attack mode 1 (combination).");

      return -1;
    }

    // detect if mask was specified:

    bool mask_is_missing = true;

    if (user_options->keyspace == true) // special case if --keyspace was used: we need the mask but no hash file
    {
      if (user_options->hc_argc > 0) mask_is_missing = false;
    }
    else if (user_options->stdout_flag == true) // special case if --stdout was used: we need the mask but no hash file
    {
      if (user_options->hc_argc > 0) mask_is_missing = false;
    }
    else
    {
      if (user_options->hc_argc > 1) mask_is_missing = false;
    }

    if (mask_is_missing == true)
    {
      event_log_error (hashcat_ctx, "If you specify a custom charset, you must also specify a mask.");

      return -1;
    }
  }

  // argc / argv checks

  bool show_error = true;

  if (user_options->version == true)
  {
    show_error = false;
  }
  else if (user_options->usage == true)
  {
    show_error = false;
  }
  #ifdef WITH_BRAIN
  else if (user_options->brain_server == true)
  {
    show_error = false;
  }
  #endif
  else if (user_options->benchmark == true)
  {
    if (user_options->hc_argc == 0)
    {
      show_error = false;
    }
  }
  else if (user_options->example_hashes == true)
  {
    if (user_options->hc_argc == 0)
    {
      show_error = false;
    }
  }
  else if (user_options->opencl_info == true)
  {
    if (user_options->hc_argc == 0)
    {
      show_error = false;
    }
  }
  else if (user_options->restore == true)
  {
    if (user_options->hc_argc == 0)
    {
      show_error = false;
    }
  }
  else if (user_options->keyspace == true)
  {
    if (user_options->attack_mode == ATTACK_MODE_STRAIGHT)
    {
      if (user_options->hc_argc == 1)
      {
        show_error = false;
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_COMBI)
    {
      if (user_options->hc_argc == 2)
      {
        show_error = false;
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_BF)
    {
      if (user_options->hc_argc == 1)
      {
        show_error = false;
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_HYBRID1)
    {
      if (user_options->hc_argc == 2)
      {
        show_error = false;
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_HYBRID2)
    {
      if (user_options->hc_argc == 2)
      {
        show_error = false;
      }
    }
  }
  else if (user_options->stdout_flag == true)
  {
    if (user_options->attack_mode == ATTACK_MODE_STRAIGHT)
    {
      // all argc possible because of stdin mode

      show_error = false;
    }
    else if (user_options->attack_mode == ATTACK_MODE_COMBI)
    {
      if (user_options->hc_argc == 2)
      {
        show_error = false;
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_BF)
    {
      if (user_options->hc_argc >= 1)
      {
        show_error = false;
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_HYBRID1)
    {
      if (user_options->hc_argc >= 1)
      {
        show_error = false;
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_HYBRID2)
    {
      if (user_options->hc_argc >= 1)
      {
        show_error = false;
      }
    }
  }
  else
  {
    if (user_options->attack_mode == ATTACK_MODE_STRAIGHT)
    {
      if (user_options->hc_argc >= 1)
      {
        show_error = false;
      }

      if (user_options->hc_argc == 1)
      {
        // stdin mode

        #ifdef WITH_BRAIN
        if (user_options->brain_client == true)
        {
          event_log_error (hashcat_ctx, "Use of --brain-client is not possible in stdin mode.");

          return -1;
        }
        #endif

        if (user_options->slow_candidates == true)
        {
          event_log_error (hashcat_ctx, "Use of --slow-candidates is not possible in stdin mode.");

          return -1;
        }
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_COMBI)
    {
      if (user_options->hc_argc == 3)
      {
        show_error = false;
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_BF)
    {
      if (user_options->hc_argc >= 1)
      {
        show_error = false;
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_HYBRID1)
    {
      if (user_options->hc_argc >= 2)
      {
        show_error = false;
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_HYBRID2)
    {
      if (user_options->hc_argc >= 2)
      {
        show_error = false;
      }
    }
  }

  if (show_error == true)
  {
    usage_mini_print (user_options->hc_bin);

    return -1;
  }

  return 0;
}