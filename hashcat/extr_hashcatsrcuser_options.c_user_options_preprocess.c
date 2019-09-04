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
struct TYPE_4__ {int stdout_flag; int hwmon_disable; int left; int logfile_disable; int potfile_disable; int restore_disable; int restore; int show; int status; int bitmap_min; int bitmap_max; int example_hashes; int opencl_info; int keyspace; int speed_only; int progress_only; int usage; int benchmark; scalar_t__ attack_mode; int increment; int workload_profile_chgd; int optimized_kernel_enable; int workload_profile; int quiet; int slow_candidates; int opencl_vector_width; int force; int hash_mode; int kernel_accel; scalar_t__ skip; scalar_t__ limit; int markov_threshold; int segment_size_chgd; int segment_size; int hc_argc; void* custom_charset_3; void* custom_charset_2; void* custom_charset_1; scalar_t__ hwmon_temp_abort; int /*<<< orphan*/  outfile_format; int /*<<< orphan*/ * opencl_platforms; int /*<<< orphan*/  opencl_device_types; int /*<<< orphan*/ * opencl_devices; void* kernel_loops; scalar_t__ status_timer; scalar_t__ restore_timer; scalar_t__ spin_damp; scalar_t__ outfile_check_timer; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_5__ {TYPE_1__* user_options; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 scalar_t__ ATTACK_MODE_BF ; 
 scalar_t__ ATTACK_MODE_COMBI ; 
 scalar_t__ ATTACK_MODE_HYBRID1 ; 
 scalar_t__ ATTACK_MODE_HYBRID2 ; 
 scalar_t__ ATTACK_MODE_NONE ; 
 scalar_t__ ATTACK_MODE_STRAIGHT ; 
 void* DEF_MASK_CS_1 ; 
 void* DEF_MASK_CS_2 ; 
 void* DEF_MASK_CS_3 ; 
 void* KERNEL_BFS ; 
 void* KERNEL_COMBS ; 
 void* KERNEL_RULES ; 
 int /*<<< orphan*/  OUTFILE_FMT_HASH ; 
 int /*<<< orphan*/  OUTFILE_FMT_PLAIN ; 
 int /*<<< orphan*/  hcstrdup (char*) ; 

void user_options_preprocess (hashcat_ctx_t *hashcat_ctx)
{
  user_options_t *user_options = hashcat_ctx->user_options;

  // some options can influence or overwrite other options

  #ifdef WITH_BRAIN
  if (user_options->brain_client == true)
  {
    user_options->slow_candidates = true;
  }
  #endif

  if (user_options->stdout_flag)
  {
    user_options->hwmon_disable       = true;
    user_options->left                = false;
    user_options->logfile_disable     = true;
    user_options->spin_damp           = 0;
    user_options->outfile_check_timer = 0;
    user_options->potfile_disable     = true;
    user_options->restore_disable     = true;
    user_options->restore             = false;
    user_options->restore_timer       = 0;
    user_options->show                = false;
    user_options->status              = false;
    user_options->status_timer        = 0;
    user_options->bitmap_min          = 1;
    user_options->bitmap_max          = 1;
  }

  if (user_options->example_hashes  == true
   || user_options->opencl_info     == true
   || user_options->keyspace        == true
   || user_options->speed_only      == true
   || user_options->progress_only   == true
   || user_options->usage           == true)
  {
    user_options->hwmon_disable       = true;
    user_options->left                = false;
    user_options->logfile_disable     = true;
    user_options->spin_damp           = 0;
    user_options->outfile_check_timer = 0;
    user_options->potfile_disable     = true;
    user_options->restore_disable     = true;
    user_options->restore             = false;
    user_options->restore_timer       = 0;
    user_options->show                = false;
    user_options->status              = false;
    user_options->status_timer        = 0;
    user_options->bitmap_min          = 1;
    user_options->bitmap_max          = 1;
    #ifdef WITH_BRAIN
    user_options->brain_client        = false;
    #endif
  }

  if (user_options->benchmark == true)
  {
    user_options->attack_mode         = ATTACK_MODE_BF;
    user_options->hwmon_temp_abort    = 0;
    user_options->increment           = false;
    user_options->left                = false;
    user_options->logfile_disable     = true;
    user_options->spin_damp           = 0;
    user_options->potfile_disable     = true;
    user_options->progress_only       = false;
    user_options->restore_disable     = true;
    user_options->restore             = false;
    user_options->restore_timer       = 0;
    user_options->show                = false;
    user_options->speed_only          = true;
    user_options->status              = false;
    user_options->status_timer        = 0;
    user_options->bitmap_min          = 1;
    user_options->bitmap_max          = 1;
    #ifdef WITH_BRAIN
    user_options->brain_client        = false;
    #endif

    if (user_options->workload_profile_chgd == false)
    {
      user_options->optimized_kernel_enable = true;
      user_options->workload_profile        = 3;
    }
  }

  if (user_options->example_hashes == true)
  {
    user_options->quiet = true;
  }

  if (user_options->usage == true)
  {
    user_options->quiet = true;
  }

  if (user_options->progress_only == true)
  {
    user_options->speed_only = true;
  }

  if (user_options->keyspace == true)
  {
    user_options->quiet = true;
  }

  if (user_options->slow_candidates == true)
  {
    user_options->opencl_vector_width = 1;
  }

  if (user_options->stdout_flag == true)
  {
    user_options->force               = true;
    user_options->hash_mode           = 2000;
    user_options->kernel_accel        = 1024;
    user_options->opencl_vector_width = 1;
    user_options->outfile_format      = OUTFILE_FMT_PLAIN;
    user_options->quiet               = true;

    if (user_options->attack_mode == ATTACK_MODE_STRAIGHT)
    {
      user_options->kernel_loops = KERNEL_RULES;
    }
    else if (user_options->attack_mode == ATTACK_MODE_COMBI)
    {
      user_options->kernel_loops = KERNEL_COMBS;
    }
    else if (user_options->attack_mode == ATTACK_MODE_BF)
    {
      user_options->kernel_loops = KERNEL_BFS;
    }
    else if (user_options->attack_mode == ATTACK_MODE_HYBRID1)
    {
      user_options->kernel_loops = KERNEL_COMBS;
    }
    else if (user_options->attack_mode == ATTACK_MODE_HYBRID2)
    {
      user_options->kernel_loops = KERNEL_COMBS;
    }
  }

  if (user_options->opencl_info == true)
  {
    user_options->opencl_devices      = NULL;
    user_options->opencl_device_types = hcstrdup ("1,2,3");
    user_options->opencl_platforms    = NULL;
    user_options->quiet               = true;
  }

  if (user_options->left == true)
  {
    user_options->outfile_format = OUTFILE_FMT_HASH;
  }

  if (user_options->show == true || user_options->left == true)
  {
    user_options->attack_mode = ATTACK_MODE_NONE;
    user_options->quiet       = true;
  }

  // this allows the user to use --show and --left while cracking (i.e. while another instance of hashcat is running)
  if (user_options->show == true || user_options->left == true)
  {
    user_options->restore_disable = true;

    user_options->restore = false;
  }

  if (user_options->skip != 0 && user_options->limit != 0)
  {
    user_options->limit += user_options->skip;
  }

  if (user_options->markov_threshold == 0)
  {
    user_options->markov_threshold = 0x100;
  }

  if (user_options->segment_size_chgd == true)
  {
    user_options->segment_size *= (1024 * 1024);
  }

  #if !defined (WITH_HWMON)
  user_options->hwmon_disable = true;
  #endif // WITH_HWMON

  if (user_options->hwmon_disable == true)
  {
    user_options->hwmon_temp_abort = 0;
  }

  // default mask

  if (user_options->attack_mode == ATTACK_MODE_BF)
  {
    if (user_options->example_hashes == true)
    {

    }
    else if (user_options->opencl_info == true)
    {

    }
    else if (user_options->speed_only == true)
    {

    }
    else if (user_options->keyspace == true)
    {
      if (user_options->hc_argc == 0)
      {
        user_options->custom_charset_1 = DEF_MASK_CS_1;
        user_options->custom_charset_2 = DEF_MASK_CS_2;
        user_options->custom_charset_3 = DEF_MASK_CS_3;

        user_options->increment = true;
      }
    }
    else if (user_options->stdout_flag == true)
    {
      if (user_options->hc_argc == 0)
      {
        user_options->custom_charset_1 = DEF_MASK_CS_1;
        user_options->custom_charset_2 = DEF_MASK_CS_2;
        user_options->custom_charset_3 = DEF_MASK_CS_3;

        user_options->increment = true;
      }
    }
    else
    {
      if (user_options->hc_argc == 1)
      {
        user_options->custom_charset_1 = DEF_MASK_CS_1;
        user_options->custom_charset_2 = DEF_MASK_CS_2;
        user_options->custom_charset_3 = DEF_MASK_CS_3;

        user_options->increment = true;
      }
    }
  }
}