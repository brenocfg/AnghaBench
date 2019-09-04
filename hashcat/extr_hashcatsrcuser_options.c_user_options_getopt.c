#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int usage; int version; int restore; int quiet; int show; int left; int advice_disable; int username; int remove; int remove_timer_chgd; int potfile_disable; int example_hashes; int force; int self_test_disable; int skip_chgd; int limit_chgd; int keep_guessing; int keyspace; int benchmark; int benchmark_all; int stdout_flag; int stdin_timeout_abort_chgd; int speed_only; int progress_only; int restore_disable; int status; int status_json; int machine_readable; int loopback; int hash_mode_chgd; int runtime_chgd; int attack_mode_chgd; int rp_gen_seed_chgd; int markov_disable; int markov_classic; int outfile_format_chgd; int outfile_autohex; int wordlist_autohex_disable; int hex_charset; int hex_salt; int hex_wordlist; int opencl_info; int opencl_vector_width_chgd; int optimized_kernel_enable; int workload_profile_chgd; int kernel_accel_chgd; int kernel_loops_chgd; int kernel_threads_chgd; int spin_damp_chgd; int hwmon_disable; int logfile_disable; int hccapx_message_pair_chgd; int nonce_error_corrections_chgd; int segment_size_chgd; int increment; int increment_min_chgd; int increment_max_chgd; int slow_candidates; char* hc_bin; int hc_argc; char** hc_argv; int /*<<< orphan*/ * custom_charset_4; int /*<<< orphan*/ * custom_charset_3; int /*<<< orphan*/ * custom_charset_2; int /*<<< orphan*/ * custom_charset_1; void* increment_max; void* increment_min; void* bitmap_max; void* bitmap_min; int /*<<< orphan*/  separator; void* scrypt_tmto; void* segment_size; void* veracrypt_pim_stop; void* veracrypt_pim_start; int /*<<< orphan*/ * veracrypt_keyfiles; int /*<<< orphan*/ * truecrypt_keyfiles; int /*<<< orphan*/ * keyboard_layout_mapping; void* nonce_error_corrections; void* hccapx_message_pair; void* hwmon_temp_abort; void* spin_damp; void* kernel_threads; void* kernel_loops; void* kernel_accel; void* workload_profile; void* opencl_vector_width; int /*<<< orphan*/ * opencl_device_types; int /*<<< orphan*/ * opencl_platforms; int /*<<< orphan*/ * opencl_devices; int /*<<< orphan*/ * cpu_affinity; void* outfile_check_timer; void* outfile_format; int /*<<< orphan*/ * outfile; int /*<<< orphan*/ * markov_hcstat2; void* markov_threshold; int /*<<< orphan*/ * rule_buf_r; int /*<<< orphan*/ * rule_buf_l; void* rp_gen_seed; void* rp_gen_func_max; void* rp_gen_func_min; void* rp_gen; int /*<<< orphan*/  rp_files_cnt; int /*<<< orphan*/ ** rp_files; void* attack_mode; void* runtime; void* hash_mode; int /*<<< orphan*/ * session; void* status_timer; int /*<<< orphan*/ * restore_file_path; void* stdin_timeout_abort; void* limit; void* skip; int /*<<< orphan*/ * outfile_check_dir; int /*<<< orphan*/ * induction_dir; int /*<<< orphan*/ * encoding_to; int /*<<< orphan*/ * encoding_from; int /*<<< orphan*/ * debug_file; void* debug_mode; int /*<<< orphan*/ * potfile_path; void* remove_timer; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_6__ {TYPE_1__* user_options; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
#define  IDX_ADVICE_DISABLE 223 
#define  IDX_ATTACK_MODE 222 
#define  IDX_BENCHMARK 221 
#define  IDX_BENCHMARK_ALL 220 
#define  IDX_BITMAP_MAX 219 
#define  IDX_BITMAP_MIN 218 
#define  IDX_CPU_AFFINITY 217 
#define  IDX_CUSTOM_CHARSET_1 216 
#define  IDX_CUSTOM_CHARSET_2 215 
#define  IDX_CUSTOM_CHARSET_3 214 
#define  IDX_CUSTOM_CHARSET_4 213 
#define  IDX_DEBUG_FILE 212 
#define  IDX_DEBUG_MODE 211 
#define  IDX_ENCODING_FROM 210 
#define  IDX_ENCODING_TO 209 
#define  IDX_EXAMPLE_HASHES 208 
#define  IDX_FORCE 207 
#define  IDX_HASH_MODE 206 
#define  IDX_HCCAPX_MESSAGE_PAIR 205 
#define  IDX_HELP 204 
#define  IDX_HEX_CHARSET 203 
#define  IDX_HEX_SALT 202 
#define  IDX_HEX_WORDLIST 201 
#define  IDX_HWMON_DISABLE 200 
#define  IDX_HWMON_TEMP_ABORT 199 
#define  IDX_INCREMENT 198 
#define  IDX_INCREMENT_MAX 197 
#define  IDX_INCREMENT_MIN 196 
#define  IDX_INDUCTION_DIR 195 
#define  IDX_KEEP_GUESSING 194 
#define  IDX_KERNEL_ACCEL 193 
#define  IDX_KERNEL_LOOPS 192 
#define  IDX_KERNEL_THREADS 191 
#define  IDX_KEYBOARD_LAYOUT_MAPPING 190 
#define  IDX_KEYSPACE 189 
#define  IDX_LEFT 188 
#define  IDX_LIMIT 187 
#define  IDX_LOGFILE_DISABLE 186 
#define  IDX_LOOPBACK 185 
#define  IDX_MACHINE_READABLE 184 
#define  IDX_MARKOV_CLASSIC 183 
#define  IDX_MARKOV_DISABLE 182 
#define  IDX_MARKOV_HCSTAT2 181 
#define  IDX_MARKOV_THRESHOLD 180 
#define  IDX_NONCE_ERROR_CORRECTIONS 179 
#define  IDX_OPENCL_DEVICES 178 
#define  IDX_OPENCL_DEVICE_TYPES 177 
#define  IDX_OPENCL_INFO 176 
#define  IDX_OPENCL_PLATFORMS 175 
#define  IDX_OPENCL_VECTOR_WIDTH 174 
#define  IDX_OPTIMIZED_KERNEL_ENABLE 173 
#define  IDX_OUTFILE 172 
#define  IDX_OUTFILE_AUTOHEX_DISABLE 171 
#define  IDX_OUTFILE_CHECK_DIR 170 
#define  IDX_OUTFILE_CHECK_TIMER 169 
#define  IDX_OUTFILE_FORMAT 168 
#define  IDX_POTFILE_DISABLE 167 
#define  IDX_POTFILE_PATH 166 
#define  IDX_PROGRESS_ONLY 165 
#define  IDX_QUIET 164 
#define  IDX_REMOVE 163 
#define  IDX_REMOVE_TIMER 162 
#define  IDX_RESTORE 161 
#define  IDX_RESTORE_DISABLE 160 
#define  IDX_RESTORE_FILE_PATH 159 
#define  IDX_RP_FILE 158 
#define  IDX_RP_GEN 157 
#define  IDX_RP_GEN_FUNC_MAX 156 
#define  IDX_RP_GEN_FUNC_MIN 155 
#define  IDX_RP_GEN_SEED 154 
#define  IDX_RULE_BUF_L 153 
#define  IDX_RULE_BUF_R 152 
#define  IDX_RUNTIME 151 
#define  IDX_SCRYPT_TMTO 150 
#define  IDX_SEGMENT_SIZE 149 
#define  IDX_SELF_TEST_DISABLE 148 
#define  IDX_SEPARATOR 147 
#define  IDX_SESSION 146 
#define  IDX_SHOW 145 
#define  IDX_SKIP 144 
#define  IDX_SLOW_CANDIDATES 143 
#define  IDX_SPEED_ONLY 142 
#define  IDX_SPIN_DAMP 141 
#define  IDX_STATUS 140 
#define  IDX_STATUS_JSON 139 
#define  IDX_STATUS_TIMER 138 
#define  IDX_STDIN_TIMEOUT_ABORT 137 
#define  IDX_STDOUT_FLAG 136 
#define  IDX_TRUECRYPT_KEYFILES 135 
#define  IDX_USERNAME 134 
#define  IDX_VERACRYPT_KEYFILES 133 
#define  IDX_VERACRYPT_PIM_START 132 
#define  IDX_VERACRYPT_PIM_STOP 131 
#define  IDX_VERSION 130 
#define  IDX_WORDLIST_AUTOHEX_DISABLE 129 
#define  IDX_WORKLOAD_PROFILE 128 
 int /*<<< orphan*/  event_log_error (TYPE_2__*,char*,...) ; 
 int getopt_long (int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int hc_string_is_digit (int /*<<< orphan*/ *) ; 
 void* hc_strtoul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* hc_strtoull (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  long_options ; 
 int /*<<< orphan*/ * optarg ; 
 int optind ; 
 scalar_t__ optopt ; 
 int /*<<< orphan*/  short_options ; 

int user_options_getopt (hashcat_ctx_t *hashcat_ctx, int argc, char **argv)
{
  user_options_t *user_options = hashcat_ctx->user_options;

  int c = -1;

  int option_index;

  optind = 1;
  optopt = 0;

  option_index = 0;

  while ((c = getopt_long (argc, argv, short_options, long_options, &option_index)) != -1)
  {
    switch (c)
    {
      case IDX_REMOVE_TIMER:
      case IDX_DEBUG_MODE:
      case IDX_SKIP:
      case IDX_LIMIT:
      case IDX_STATUS_TIMER:
      case IDX_HASH_MODE:
      case IDX_RUNTIME:
      case IDX_ATTACK_MODE:
      case IDX_RP_GEN:
      case IDX_RP_GEN_FUNC_MIN:
      case IDX_RP_GEN_FUNC_MAX:
      case IDX_RP_GEN_SEED:
      case IDX_MARKOV_THRESHOLD:
      case IDX_OUTFILE_FORMAT:
      case IDX_OUTFILE_CHECK_TIMER:
      case IDX_OPENCL_VECTOR_WIDTH:
      case IDX_WORKLOAD_PROFILE:
      case IDX_KERNEL_ACCEL:
      case IDX_KERNEL_LOOPS:
      case IDX_KERNEL_THREADS:
      case IDX_SPIN_DAMP:
      case IDX_HWMON_TEMP_ABORT:
      case IDX_HCCAPX_MESSAGE_PAIR:
      case IDX_NONCE_ERROR_CORRECTIONS:
      case IDX_VERACRYPT_PIM_START:
      case IDX_VERACRYPT_PIM_STOP:
      case IDX_SEGMENT_SIZE:
      case IDX_SCRYPT_TMTO:
      case IDX_BITMAP_MIN:
      case IDX_BITMAP_MAX:
      case IDX_INCREMENT_MIN:
      case IDX_INCREMENT_MAX:
      #ifdef WITH_BRAIN
      case IDX_BRAIN_PORT:
      #endif

      if (hc_string_is_digit (optarg) == false)
      {
        event_log_error (hashcat_ctx, "The specified parameter cannot use '%s' as a value - must be a number.", optarg);

        return -1;
      }

      break;

      case '?':
      {
        event_log_error (hashcat_ctx, "Invalid argument specified.");

        return -1;
      }
    }
  }

  optind = 1;
  optopt = 0;

  option_index = 0;

  while ((c = getopt_long (argc, argv, short_options, long_options, &option_index)) != -1)
  {
    switch (c)
    {
      case IDX_HELP:                      user_options->usage                     = true;                            break;
      case IDX_VERSION:                   user_options->version                   = true;                            break;
      case IDX_RESTORE:                   user_options->restore                   = true;                            break;
      case IDX_QUIET:                     user_options->quiet                     = true;                            break;
      case IDX_SHOW:                      user_options->show                      = true;                            break;
      case IDX_LEFT:                      user_options->left                      = true;                            break;
      case IDX_ADVICE_DISABLE:            user_options->advice_disable            = true;                            break;
      case IDX_USERNAME:                  user_options->username                  = true;                            break;
      case IDX_REMOVE:                    user_options->remove                    = true;                            break;
      case IDX_REMOVE_TIMER:              user_options->remove_timer              = hc_strtoul (optarg, NULL, 10);
                                          user_options->remove_timer_chgd         = true;                            break;
      case IDX_POTFILE_DISABLE:           user_options->potfile_disable           = true;                            break;
      case IDX_POTFILE_PATH:              user_options->potfile_path              = optarg;                          break;
      case IDX_DEBUG_MODE:                user_options->debug_mode                = hc_strtoul (optarg, NULL, 10);   break;
      case IDX_DEBUG_FILE:                user_options->debug_file                = optarg;                          break;
      case IDX_ENCODING_FROM:             user_options->encoding_from             = optarg;                          break;
      case IDX_ENCODING_TO:               user_options->encoding_to               = optarg;                          break;
      case IDX_INDUCTION_DIR:             user_options->induction_dir             = optarg;                          break;
      case IDX_OUTFILE_CHECK_DIR:         user_options->outfile_check_dir         = optarg;                          break;
      case IDX_EXAMPLE_HASHES:            user_options->example_hashes            = true;                            break;
      case IDX_FORCE:                     user_options->force                     = true;                            break;
      case IDX_SELF_TEST_DISABLE:         user_options->self_test_disable         = true;                            break;
      case IDX_SKIP:                      user_options->skip                      = hc_strtoull (optarg, NULL, 10);
                                          user_options->skip_chgd                 = true;                            break;
      case IDX_LIMIT:                     user_options->limit                     = hc_strtoull (optarg, NULL, 10);
                                          user_options->limit_chgd                = true;                            break;
      case IDX_KEEP_GUESSING:             user_options->keep_guessing             = true;                            break;
      case IDX_KEYSPACE:                  user_options->keyspace                  = true;                            break;
      case IDX_BENCHMARK:                 user_options->benchmark                 = true;                            break;
      case IDX_BENCHMARK_ALL:             user_options->benchmark_all             = true;                            break;
      case IDX_STDOUT_FLAG:               user_options->stdout_flag               = true;                            break;
      case IDX_STDIN_TIMEOUT_ABORT:       user_options->stdin_timeout_abort       = hc_strtoul (optarg, NULL, 10);
                                          user_options->stdin_timeout_abort_chgd  = true;                            break;
      case IDX_SPEED_ONLY:                user_options->speed_only                = true;                            break;
      case IDX_PROGRESS_ONLY:             user_options->progress_only             = true;                            break;
      case IDX_RESTORE_DISABLE:           user_options->restore_disable           = true;                            break;
      case IDX_RESTORE_FILE_PATH:         user_options->restore_file_path         = optarg;                          break;
      case IDX_STATUS:                    user_options->status                    = true;                            break;
	    case IDX_STATUS_JSON:               user_options->status_json               = true;                            break;
      case IDX_STATUS_TIMER:              user_options->status_timer              = hc_strtoul (optarg, NULL, 10);   break;
      case IDX_MACHINE_READABLE:          user_options->machine_readable          = true;                            break;
      case IDX_LOOPBACK:                  user_options->loopback                  = true;                            break;
      case IDX_SESSION:                   user_options->session                   = optarg;                          break;
      case IDX_HASH_MODE:                 user_options->hash_mode                 = hc_strtoul (optarg, NULL, 10);
                                          user_options->hash_mode_chgd            = true;                            break;
      case IDX_RUNTIME:                   user_options->runtime                   = hc_strtoul (optarg, NULL, 10);
                                          user_options->runtime_chgd              = true;                            break;
      case IDX_ATTACK_MODE:               user_options->attack_mode               = hc_strtoul (optarg, NULL, 10);
                                          user_options->attack_mode_chgd          = true;                            break;
      case IDX_RP_FILE:                   user_options->rp_files[user_options->rp_files_cnt++] = optarg;             break;
      case IDX_RP_GEN:                    user_options->rp_gen                    = hc_strtoul (optarg, NULL, 10);   break;
      case IDX_RP_GEN_FUNC_MIN:           user_options->rp_gen_func_min           = hc_strtoul (optarg, NULL, 10);   break;
      case IDX_RP_GEN_FUNC_MAX:           user_options->rp_gen_func_max           = hc_strtoul (optarg, NULL, 10);   break;
      case IDX_RP_GEN_SEED:               user_options->rp_gen_seed               = hc_strtoul (optarg, NULL, 10);
                                          user_options->rp_gen_seed_chgd          = true;                            break;
      case IDX_RULE_BUF_L:                user_options->rule_buf_l                = optarg;                          break;
      case IDX_RULE_BUF_R:                user_options->rule_buf_r                = optarg;                          break;
      case IDX_MARKOV_DISABLE:            user_options->markov_disable            = true;                            break;
      case IDX_MARKOV_CLASSIC:            user_options->markov_classic            = true;                            break;
      case IDX_MARKOV_THRESHOLD:          user_options->markov_threshold          = hc_strtoul (optarg, NULL, 10);   break;
      case IDX_MARKOV_HCSTAT2:            user_options->markov_hcstat2            = optarg;                          break;
      case IDX_OUTFILE:                   user_options->outfile                   = optarg;                          break;
      case IDX_OUTFILE_FORMAT:            user_options->outfile_format            = hc_strtoul (optarg, NULL, 10);
                                          user_options->outfile_format_chgd       = true;                            break;
      case IDX_OUTFILE_AUTOHEX_DISABLE:   user_options->outfile_autohex           = false;                           break;
      case IDX_OUTFILE_CHECK_TIMER:       user_options->outfile_check_timer       = hc_strtoul (optarg, NULL, 10);   break;
      case IDX_WORDLIST_AUTOHEX_DISABLE:  user_options->wordlist_autohex_disable  = true;                            break;
      case IDX_HEX_CHARSET:               user_options->hex_charset               = true;                            break;
      case IDX_HEX_SALT:                  user_options->hex_salt                  = true;                            break;
      case IDX_HEX_WORDLIST:              user_options->hex_wordlist              = true;                            break;
      case IDX_CPU_AFFINITY:              user_options->cpu_affinity              = optarg;                          break;
      case IDX_OPENCL_INFO:               user_options->opencl_info               = true;                            break;
      case IDX_OPENCL_DEVICES:            user_options->opencl_devices            = optarg;                          break;
      case IDX_OPENCL_PLATFORMS:          user_options->opencl_platforms          = optarg;                          break;
      case IDX_OPENCL_DEVICE_TYPES:       user_options->opencl_device_types       = optarg;                          break;
      case IDX_OPENCL_VECTOR_WIDTH:       user_options->opencl_vector_width       = hc_strtoul (optarg, NULL, 10);
                                          user_options->opencl_vector_width_chgd  = true;                            break;
      case IDX_OPTIMIZED_KERNEL_ENABLE:   user_options->optimized_kernel_enable   = true;                            break;
      case IDX_WORKLOAD_PROFILE:          user_options->workload_profile          = hc_strtoul (optarg, NULL, 10);
                                          user_options->workload_profile_chgd     = true;                            break;
      case IDX_KERNEL_ACCEL:              user_options->kernel_accel              = hc_strtoul (optarg, NULL, 10);
                                          user_options->kernel_accel_chgd         = true;                            break;
      case IDX_KERNEL_LOOPS:              user_options->kernel_loops              = hc_strtoul (optarg, NULL, 10);
                                          user_options->kernel_loops_chgd         = true;                            break;
      case IDX_KERNEL_THREADS:            user_options->kernel_threads            = hc_strtoul (optarg, NULL, 10);
                                          user_options->kernel_threads_chgd       = true;                            break;
      case IDX_SPIN_DAMP:                 user_options->spin_damp                 = hc_strtoul (optarg, NULL, 10);
                                          user_options->spin_damp_chgd            = true;                            break;
      case IDX_HWMON_DISABLE:             user_options->hwmon_disable             = true;                            break;
      case IDX_HWMON_TEMP_ABORT:          user_options->hwmon_temp_abort          = hc_strtoul (optarg, NULL, 10);   break;
      case IDX_LOGFILE_DISABLE:           user_options->logfile_disable           = true;                            break;
      case IDX_HCCAPX_MESSAGE_PAIR:       user_options->hccapx_message_pair       = hc_strtoul (optarg, NULL, 10);
                                          user_options->hccapx_message_pair_chgd  = true;                            break;
      case IDX_NONCE_ERROR_CORRECTIONS:   user_options->nonce_error_corrections   = hc_strtoul (optarg, NULL, 10);
                                          user_options->nonce_error_corrections_chgd = true;                         break;
      case IDX_KEYBOARD_LAYOUT_MAPPING:   user_options->keyboard_layout_mapping   = optarg;                          break;
      case IDX_TRUECRYPT_KEYFILES:        user_options->truecrypt_keyfiles        = optarg;                          break;
      case IDX_VERACRYPT_KEYFILES:        user_options->veracrypt_keyfiles        = optarg;                          break;
      case IDX_VERACRYPT_PIM_START:       user_options->veracrypt_pim_start       = hc_strtoul (optarg, NULL, 10);   break;
      case IDX_VERACRYPT_PIM_STOP:        user_options->veracrypt_pim_stop        = hc_strtoul (optarg, NULL, 10);   break;
      case IDX_SEGMENT_SIZE:              user_options->segment_size              = hc_strtoul (optarg, NULL, 10);
                                          user_options->segment_size_chgd         = true;                            break;
      case IDX_SCRYPT_TMTO:               user_options->scrypt_tmto               = hc_strtoul (optarg, NULL, 10);   break;
      case IDX_SEPARATOR:                 user_options->separator                 = optarg[0];                       break;
      case IDX_BITMAP_MIN:                user_options->bitmap_min                = hc_strtoul (optarg, NULL, 10);   break;
      case IDX_BITMAP_MAX:                user_options->bitmap_max                = hc_strtoul (optarg, NULL, 10);   break;
      case IDX_INCREMENT:                 user_options->increment                 = true;                            break;
      case IDX_INCREMENT_MIN:             user_options->increment_min             = hc_strtoul (optarg, NULL, 10);
                                          user_options->increment_min_chgd        = true;                            break;
      case IDX_INCREMENT_MAX:             user_options->increment_max             = hc_strtoul (optarg, NULL, 10);
                                          user_options->increment_max_chgd        = true;                            break;
      case IDX_CUSTOM_CHARSET_1:          user_options->custom_charset_1          = optarg;                          break;
      case IDX_CUSTOM_CHARSET_2:          user_options->custom_charset_2          = optarg;                          break;
      case IDX_CUSTOM_CHARSET_3:          user_options->custom_charset_3          = optarg;                          break;
      case IDX_CUSTOM_CHARSET_4:          user_options->custom_charset_4          = optarg;                          break;
      case IDX_SLOW_CANDIDATES:           user_options->slow_candidates           = true;                            break;
      #ifdef WITH_BRAIN
      case IDX_BRAIN_CLIENT:              user_options->brain_client              = true;                            break;
      case IDX_BRAIN_CLIENT_FEATURES:     user_options->brain_client_features     = hc_strtoul (optarg, NULL, 10);   break;
      case IDX_BRAIN_SERVER:              user_options->brain_server              = true;                            break;
      case IDX_BRAIN_PASSWORD:            user_options->brain_password            = optarg;
                                          user_options->brain_password_chgd       = true;                            break;
      case IDX_BRAIN_HOST:                user_options->brain_host                = optarg;
                                          user_options->brain_host_chgd           = true;                            break;
      case IDX_BRAIN_PORT:                user_options->brain_port                = hc_strtoul (optarg, NULL, 10);
                                          user_options->brain_port_chgd           = true;                            break;
      case IDX_BRAIN_SESSION:             user_options->brain_session             = hc_strtoul (optarg, NULL, 16);   break;
      case IDX_BRAIN_SESSION_WHITELIST:   user_options->brain_session_whitelist   = optarg;                          break;
      #endif
    }
  }

  user_options->hc_bin = argv[0];

  user_options->hc_argc = argc - optind;
  user_options->hc_argv = argv + optind;

  return 0;
}