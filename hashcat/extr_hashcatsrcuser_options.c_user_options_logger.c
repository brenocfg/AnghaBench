#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  workload_profile; int /*<<< orphan*/  version; int /*<<< orphan*/  veracrypt_pim_stop; int /*<<< orphan*/  veracrypt_pim_start; int /*<<< orphan*/  username; int /*<<< orphan*/  usage; int /*<<< orphan*/  stdout_flag; int /*<<< orphan*/  status_timer; int /*<<< orphan*/  status_json; int /*<<< orphan*/  status; int /*<<< orphan*/  spin_damp; int /*<<< orphan*/  speed_only; int /*<<< orphan*/  show; int /*<<< orphan*/  slow_candidates; int /*<<< orphan*/  self_test_disable; int /*<<< orphan*/  segment_size; int /*<<< orphan*/  scrypt_tmto; int /*<<< orphan*/  runtime; int /*<<< orphan*/  rp_gen_seed; int /*<<< orphan*/  rp_gen_func_min; int /*<<< orphan*/  rp_gen_func_max; int /*<<< orphan*/  rp_gen; int /*<<< orphan*/  rp_files_cnt; int /*<<< orphan*/  restore_timer; int /*<<< orphan*/  restore_disable; int /*<<< orphan*/  restore; int /*<<< orphan*/  remove_timer; int /*<<< orphan*/  remove; int /*<<< orphan*/  quiet; int /*<<< orphan*/  progress_only; int /*<<< orphan*/  potfile_disable; int /*<<< orphan*/  wordlist_autohex_disable; int /*<<< orphan*/  outfile_format; int /*<<< orphan*/  outfile_check_timer; int /*<<< orphan*/  outfile_autohex; int /*<<< orphan*/  optimized_kernel_enable; int /*<<< orphan*/  opencl_vector_width; int /*<<< orphan*/  opencl_info; int /*<<< orphan*/  markov_threshold; int /*<<< orphan*/  markov_disable; int /*<<< orphan*/  markov_classic; int /*<<< orphan*/  machine_readable; int /*<<< orphan*/  loopback; int /*<<< orphan*/  logfile_disable; int /*<<< orphan*/  left; int /*<<< orphan*/  keyspace; int /*<<< orphan*/  kernel_threads; int /*<<< orphan*/  kernel_loops; int /*<<< orphan*/  kernel_accel; int /*<<< orphan*/  keep_guessing; int /*<<< orphan*/  increment_min; int /*<<< orphan*/  increment_max; int /*<<< orphan*/  increment; int /*<<< orphan*/  hex_wordlist; int /*<<< orphan*/  hex_salt; int /*<<< orphan*/  hex_charset; int /*<<< orphan*/  hash_mode; int /*<<< orphan*/  hwmon_temp_abort; int /*<<< orphan*/  hwmon_disable; int /*<<< orphan*/  force; int /*<<< orphan*/  example_hashes; int /*<<< orphan*/  debug_mode; int /*<<< orphan*/  bitmap_min; int /*<<< orphan*/  bitmap_max; int /*<<< orphan*/  benchmark_all; int /*<<< orphan*/  benchmark; int /*<<< orphan*/  attack_mode; int /*<<< orphan*/  skip; int /*<<< orphan*/  limit; int /*<<< orphan*/  veracrypt_keyfiles; int /*<<< orphan*/  truecrypt_keyfiles; int /*<<< orphan*/  session; int /*<<< orphan*/  rule_buf_r; int /*<<< orphan*/  rule_buf_l; int /*<<< orphan*/ * rp_files; int /*<<< orphan*/  restore_file_path; int /*<<< orphan*/  potfile_path; int /*<<< orphan*/  outfile_check_dir; int /*<<< orphan*/  outfile; int /*<<< orphan*/  opencl_platforms; int /*<<< orphan*/  opencl_device_types; int /*<<< orphan*/  opencl_devices; int /*<<< orphan*/  markov_hcstat2; int /*<<< orphan*/  keyboard_layout_mapping; int /*<<< orphan*/  induction_dir; int /*<<< orphan*/  encoding_to; int /*<<< orphan*/  encoding_from; int /*<<< orphan*/  debug_file; int /*<<< orphan*/  custom_charset_4; int /*<<< orphan*/  custom_charset_3; int /*<<< orphan*/  custom_charset_2; int /*<<< orphan*/  custom_charset_1; int /*<<< orphan*/  cpu_affinity; int /*<<< orphan*/  separator; } ;
typedef  TYPE_1__ user_options_t ;
typedef  int /*<<< orphan*/  logfile_ctx_t ;
struct TYPE_5__ {int /*<<< orphan*/ * logfile_ctx; TYPE_1__* user_options; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  logfile_top_char (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logfile_top_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logfile_top_uint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logfile_top_uint64 (int /*<<< orphan*/ ) ; 

void user_options_logger (hashcat_ctx_t *hashcat_ctx)
{
  user_options_t *user_options = hashcat_ctx->user_options;
  logfile_ctx_t  *logfile_ctx  = hashcat_ctx->logfile_ctx;

  logfile_top_char   (user_options->separator);
  #ifdef WITH_BRAIN
  logfile_top_string (user_options->brain_session_whitelist);
  #endif
  logfile_top_string (user_options->cpu_affinity);
  logfile_top_string (user_options->custom_charset_1);
  logfile_top_string (user_options->custom_charset_2);
  logfile_top_string (user_options->custom_charset_3);
  logfile_top_string (user_options->custom_charset_4);
  logfile_top_string (user_options->debug_file);
  logfile_top_string (user_options->encoding_from);
  logfile_top_string (user_options->encoding_to);
  logfile_top_string (user_options->induction_dir);
  logfile_top_string (user_options->keyboard_layout_mapping);
  logfile_top_string (user_options->markov_hcstat2);
  logfile_top_string (user_options->opencl_devices);
  logfile_top_string (user_options->opencl_device_types);
  logfile_top_string (user_options->opencl_platforms);
  logfile_top_string (user_options->outfile);
  logfile_top_string (user_options->outfile_check_dir);
  logfile_top_string (user_options->potfile_path);
  logfile_top_string (user_options->restore_file_path);
  logfile_top_string (user_options->rp_files[0]);
  logfile_top_string (user_options->rule_buf_l);
  logfile_top_string (user_options->rule_buf_r);
  logfile_top_string (user_options->session);
  logfile_top_string (user_options->truecrypt_keyfiles);
  logfile_top_string (user_options->veracrypt_keyfiles);
  #ifdef WITH_BRAIN
  logfile_top_string (user_options->brain_host);
  #endif
  logfile_top_uint64 (user_options->limit);
  logfile_top_uint64 (user_options->skip);
  logfile_top_uint   (user_options->attack_mode);
  logfile_top_uint   (user_options->benchmark);
  logfile_top_uint   (user_options->benchmark_all);
  logfile_top_uint   (user_options->bitmap_max);
  logfile_top_uint   (user_options->bitmap_min);
  logfile_top_uint   (user_options->debug_mode);
  logfile_top_uint   (user_options->example_hashes);
  logfile_top_uint   (user_options->force);
  logfile_top_uint   (user_options->hwmon_disable);
  logfile_top_uint   (user_options->hwmon_temp_abort);
  logfile_top_uint   (user_options->hash_mode);
  logfile_top_uint   (user_options->hex_charset);
  logfile_top_uint   (user_options->hex_salt);
  logfile_top_uint   (user_options->hex_wordlist);
  logfile_top_uint   (user_options->increment);
  logfile_top_uint   (user_options->increment_max);
  logfile_top_uint   (user_options->increment_min);
  logfile_top_uint   (user_options->keep_guessing);
  logfile_top_uint   (user_options->kernel_accel);
  logfile_top_uint   (user_options->kernel_loops);
  logfile_top_uint   (user_options->kernel_threads);
  logfile_top_uint   (user_options->keyspace);
  logfile_top_uint   (user_options->left);
  logfile_top_uint   (user_options->logfile_disable);
  logfile_top_uint   (user_options->loopback);
  logfile_top_uint   (user_options->machine_readable);
  logfile_top_uint   (user_options->markov_classic);
  logfile_top_uint   (user_options->markov_disable);
  logfile_top_uint   (user_options->markov_threshold);
  logfile_top_uint   (user_options->opencl_info);
  logfile_top_uint   (user_options->opencl_vector_width);
  logfile_top_uint   (user_options->optimized_kernel_enable);
  logfile_top_uint   (user_options->outfile_autohex);
  logfile_top_uint   (user_options->outfile_check_timer);
  logfile_top_uint   (user_options->outfile_format);
  logfile_top_uint   (user_options->wordlist_autohex_disable);
  logfile_top_uint   (user_options->potfile_disable);
  logfile_top_uint   (user_options->progress_only);
  logfile_top_uint   (user_options->quiet);
  logfile_top_uint   (user_options->remove);
  logfile_top_uint   (user_options->remove_timer);
  logfile_top_uint   (user_options->restore);
  logfile_top_uint   (user_options->restore_disable);
  logfile_top_uint   (user_options->restore_timer);
  logfile_top_uint   (user_options->rp_files_cnt);
  logfile_top_uint   (user_options->rp_gen);
  logfile_top_uint   (user_options->rp_gen_func_max);
  logfile_top_uint   (user_options->rp_gen_func_min);
  logfile_top_uint   (user_options->rp_gen_seed);
  logfile_top_uint   (user_options->runtime);
  logfile_top_uint   (user_options->scrypt_tmto);
  logfile_top_uint   (user_options->segment_size);
  logfile_top_uint   (user_options->self_test_disable);
  logfile_top_uint   (user_options->slow_candidates);
  logfile_top_uint   (user_options->show);
  logfile_top_uint   (user_options->speed_only);
  logfile_top_uint   (user_options->spin_damp);
  logfile_top_uint   (user_options->status);
  logfile_top_uint   (user_options->status_json);
  logfile_top_uint   (user_options->status_timer);
  logfile_top_uint   (user_options->stdout_flag);
  logfile_top_uint   (user_options->usage);
  logfile_top_uint   (user_options->username);
  logfile_top_uint   (user_options->veracrypt_pim_start);
  logfile_top_uint   (user_options->veracrypt_pim_stop);
  logfile_top_uint   (user_options->version);
  logfile_top_uint   (user_options->workload_profile);
  #ifdef WITH_BRAIN
  logfile_top_uint   (user_options->brain_client);
  logfile_top_uint   (user_options->brain_client_features);
  logfile_top_uint   (user_options->brain_server);
  logfile_top_uint   (user_options->brain_port);
  logfile_top_uint   (user_options->brain_session);
  #endif
}