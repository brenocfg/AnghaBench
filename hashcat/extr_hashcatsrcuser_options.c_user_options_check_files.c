#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ attack_mode; char** rp_files; char* keyboard_layout_mapping; scalar_t__ rp_files_cnt; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_19__ {char* hc_hash; int hc_workc; char** hc_workv; } ;
typedef  TYPE_2__ user_options_extra_t ;
struct TYPE_20__ {int enabled; char* filename; } ;
typedef  TYPE_3__ potfile_ctx_t ;
struct TYPE_21__ {char* filename; } ;
typedef  TYPE_4__ pidfile_ctx_t ;
struct TYPE_22__ {char* filename; } ;
typedef  TYPE_5__ outfile_ctx_t ;
struct TYPE_23__ {int enabled; char* root_directory; } ;
typedef  TYPE_6__ outcheck_ctx_t ;
struct TYPE_24__ {int enabled; char* logfile; } ;
typedef  TYPE_7__ logfile_ctx_t ;
struct TYPE_25__ {TYPE_1__* user_options; TYPE_2__* user_options_extra; TYPE_3__* potfile_ctx; TYPE_4__* pidfile_ctx; TYPE_5__* outfile_ctx; TYPE_6__* outcheck_ctx; TYPE_7__* logfile_ctx; TYPE_9__* folder_config; TYPE_10__* dictstat_ctx; } ;
typedef  TYPE_8__ hashcat_ctx_t ;
struct TYPE_26__ {char const* cwd; char const* install_dir; char const* profile_dir; char* session_dir; char const* shared_dir; char const* cpath_real; } ;
typedef  TYPE_9__ folder_config_t ;
struct TYPE_17__ {int enabled; char* filename; } ;
typedef  TYPE_10__ dictstat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTACK_EXEC_OUTSIDE_KERNEL ; 
 int /*<<< orphan*/  ATTACK_KERN_STRAIGHT ; 
 scalar_t__ ATTACK_MODE_BF ; 
 scalar_t__ ATTACK_MODE_COMBI ; 
 scalar_t__ ATTACK_MODE_HYBRID1 ; 
 scalar_t__ ATTACK_MODE_HYBRID2 ; 
 scalar_t__ ATTACK_MODE_STRAIGHT ; 
 int /*<<< orphan*/  HCBUFSIZ_TINY ; 
 int chdir (char const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_log_error (TYPE_8__*,char*,...) ; 
 int /*<<< orphan*/  event_log_warning (TYPE_8__*,char*) ; 
 int /*<<< orphan*/  generate_source_kernel_filename (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  hashconfig_destroy (TYPE_8__*) ; 
 int hashconfig_init (TYPE_8__*) ; 
 int hc_path_create (char const*) ; 
 int hc_path_exist (char*) ; 
 int hc_path_has_bom (char*) ; 
 int hc_path_is_directory (char*) ; 
 int hc_path_read (char const*) ; 
 int hc_path_write (char*) ; 
 int hc_same_files (char const*,char*) ; 
 int /*<<< orphan*/  hcfree (char*) ; 
 scalar_t__ hcmalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_filename (TYPE_9__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int user_options_check_files (hashcat_ctx_t *hashcat_ctx)
{
  dictstat_ctx_t       *dictstat_ctx       = hashcat_ctx->dictstat_ctx;
  folder_config_t      *folder_config      = hashcat_ctx->folder_config;
  logfile_ctx_t        *logfile_ctx        = hashcat_ctx->logfile_ctx;
  outcheck_ctx_t       *outcheck_ctx       = hashcat_ctx->outcheck_ctx;
  outfile_ctx_t        *outfile_ctx        = hashcat_ctx->outfile_ctx;
  pidfile_ctx_t        *pidfile_ctx        = hashcat_ctx->pidfile_ctx;
  potfile_ctx_t        *potfile_ctx        = hashcat_ctx->potfile_ctx;
  user_options_extra_t *user_options_extra = hashcat_ctx->user_options_extra;
  user_options_t       *user_options       = hashcat_ctx->user_options;

  // brain

  #ifdef WITH_BRAIN
  if (user_options->brain_host)
  {
    struct addrinfo hints;

    memset (&hints, 0, sizeof (hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *address_info = NULL;

    const int rc_getaddrinfo = getaddrinfo (user_options->brain_host, NULL, &hints, &address_info);

    if (rc_getaddrinfo != 0)
    {
      fprintf (stderr, "%s: %s\n", user_options->brain_host, gai_strerror (rc_getaddrinfo));

      return -1;
    }

    freeaddrinfo (address_info);
  }
  #endif

  // common folders

  #if defined (_WIN)
  if (hc_path_read (".") == false)
  {
    event_log_error (hashcat_ctx, "%s: %s", ".", strerror (errno));

    return -1;
  }
  #else
  if (hc_path_read (folder_config->cwd) == false)
  {
    event_log_error (hashcat_ctx, "%s: %s", folder_config->cwd, strerror (errno));

    return -1;
  }
  #endif

  if (hc_path_read (folder_config->install_dir) == false)
  {
    event_log_error (hashcat_ctx, "%s: %s", folder_config->install_dir, strerror (errno));

    return -1;
  }

  if (hc_path_read (folder_config->profile_dir) == false)
  {
    event_log_error (hashcat_ctx, "%s: %s", folder_config->profile_dir, strerror (errno));

    return -1;
  }

  if (hc_path_write (folder_config->session_dir) == false)
  {
    event_log_error (hashcat_ctx, "%s: %s", folder_config->session_dir, strerror (errno));

    return -1;
  }

  if (hc_path_read (folder_config->shared_dir) == false)
  {
    event_log_error (hashcat_ctx, "%s: %s", folder_config->shared_dir, strerror (errno));

    return -1;
  }

  if (hc_path_read (folder_config->cpath_real) == false)
  {
    event_log_error (hashcat_ctx, "%s: %s", folder_config->cpath_real, strerror (errno));

    return -1;
  }

  // hashfile - can be NULL

  if (user_options_extra->hc_hash != NULL)
  {
    if (hc_path_exist (user_options_extra->hc_hash) == true)
    {
      if (hc_path_is_directory (user_options_extra->hc_hash) == true)
      {
        event_log_error (hashcat_ctx, "%s: A directory cannot be used as a hashfile argument.", user_options_extra->hc_hash);

        return -1;
      }

      if (hc_path_read (user_options_extra->hc_hash) == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", user_options_extra->hc_hash, strerror (errno));

        return -1;
      }

      if (hc_path_has_bom (user_options_extra->hc_hash) == true)
      {
        event_log_error (hashcat_ctx, "%s: Byte Order Mark (BOM) was detected", user_options_extra->hc_hash);

        return -1;
      }
    }
  }

  // arguments - checks must depend on attack_mode

  if (user_options->attack_mode == ATTACK_MODE_STRAIGHT)
  {
    for (int i = 0; i < user_options_extra->hc_workc; i++)
    {
      char *wlfile = user_options_extra->hc_workv[i];

      if (hc_path_exist (wlfile) == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", wlfile, strerror (errno));

        return -1;
      }
    }

    for (int i = 0; i < (int) user_options->rp_files_cnt; i++)
    {
      char *rp_file = user_options->rp_files[i];

      if (hc_path_exist (rp_file) == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", rp_file, strerror (errno));

        return -1;
      }

      if (hc_path_is_directory (rp_file) == true)
      {
        event_log_error (hashcat_ctx, "%s: A directory cannot be used as a rulefile argument.", rp_file);

        return -1;
      }

      if (hc_path_read (rp_file) == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", rp_file, strerror (errno));

        return -1;
      }

      if (hc_path_has_bom (rp_file) == true)
      {
        event_log_error (hashcat_ctx, "%s: Byte Order Mark (BOM) was detected", rp_file);

        return -1;
      }
    }
  }
  else if (user_options->attack_mode == ATTACK_MODE_COMBI)
  {
    // mode easy mode here because both files must exist and readable

    if (user_options_extra->hc_workc == 2)
    {
      char *dictfile1 = user_options_extra->hc_workv[0];
      char *dictfile2 = user_options_extra->hc_workv[1];

      if (hc_path_exist (dictfile1) == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", dictfile1, strerror (errno));

        return -1;
      }

      if (hc_path_is_directory (dictfile1) == true)
      {
        event_log_error (hashcat_ctx, "%s: A directory cannot be used as a wordlist argument.", dictfile1);

        return -1;
      }

      if (hc_path_read (dictfile1) == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", dictfile1, strerror (errno));

        return -1;
      }

      if (hc_path_has_bom (dictfile1) == true)
      {
        event_log_error (hashcat_ctx, "%s: Byte Order Mark (BOM) was detected", dictfile1);

        return -1;
      }

      if (hc_path_exist (dictfile2) == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", dictfile2, strerror (errno));

        return -1;
      }

      if (hc_path_is_directory (dictfile2) == true)
      {
        event_log_error (hashcat_ctx, "%s: A directory cannot be used as a wordlist argument.", dictfile2);

        return -1;
      }

      if (hc_path_read (dictfile2) == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", dictfile2, strerror (errno));

        return -1;
      }

      if (hc_path_has_bom (dictfile2) == true)
      {
        event_log_error (hashcat_ctx, "%s: Byte Order Mark (BOM) was detected", dictfile2);

        return -1;
      }
    }
  }
  else if (user_options->attack_mode == ATTACK_MODE_BF)
  {
    // if the file exist it's a maskfile and then it must be readable

    if (user_options_extra->hc_workc == 1)
    {
      char *maskfile = user_options_extra->hc_workv[0];

      if (hc_path_exist (maskfile) == true)
      {
        if (hc_path_is_directory (maskfile) == true)
        {
          event_log_error (hashcat_ctx, "%s: A directory cannot be used as a maskfile argument.", maskfile);

          return -1;
        }

        if (hc_path_read (maskfile) == false)
        {
          event_log_error (hashcat_ctx, "%s: %s", maskfile, strerror (errno));

          return -1;
        }

        if (hc_path_has_bom (maskfile) == true)
        {
          event_log_error (hashcat_ctx, "%s: Byte Order Mark (BOM) was detected", maskfile);

          return -1;
        }
      }
    }
  }
  else if (user_options->attack_mode == ATTACK_MODE_HYBRID1)
  {
    if (user_options_extra->hc_workc == 2)
    {
      char *wlfile = user_options_extra->hc_workv[0];

      char *maskfile = user_options_extra->hc_workv[1];

      // for wordlist: can be folder

      if (hc_path_exist (wlfile) == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", wlfile, strerror (errno));

        return -1;
      }

      // for mask: if the file exist it's a maskfile and then it must be readable

      if (hc_path_exist (maskfile) == true)
      {
        if (hc_path_is_directory (maskfile) == true)
        {
          event_log_error (hashcat_ctx, "%s: A directory cannot be used as a maskfile argument.", maskfile);

          return -1;
        }

        if (hc_path_read (maskfile) == false)
        {
          event_log_error (hashcat_ctx, "%s: %s", maskfile, strerror (errno));

          return -1;
        }

        if (hc_path_has_bom (maskfile) == true)
        {
          event_log_error (hashcat_ctx, "%s: Byte Order Mark (BOM) was detected", maskfile);

          return -1;
        }
      }
    }
  }
  else if (user_options->attack_mode == ATTACK_MODE_HYBRID2)
  {
    if (user_options_extra->hc_workc == 2)
    {
      char *wlfile = user_options_extra->hc_workv[1];

      char *maskfile = user_options_extra->hc_workv[0];

      // for wordlist: can be folder

      if (hc_path_exist (wlfile) == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", wlfile, strerror (errno));

        return -1;
      }

      // for mask: if the file exist it's a maskfile and then it must be readable

      if (hc_path_exist (maskfile) == true)
      {
        if (hc_path_is_directory (maskfile) == true)
        {
          event_log_error (hashcat_ctx, "%s: A directory cannot be used as a maskfile argument.", maskfile);

          return -1;
        }

        if (hc_path_read (maskfile) == false)
        {
          event_log_error (hashcat_ctx, "%s: %s", maskfile, strerror (errno));

          return -1;
        }

        if (hc_path_has_bom (maskfile) == true)
        {
          event_log_error (hashcat_ctx, "%s: Byte Order Mark (BOM) was detected", maskfile);

          return -1;
        }
      }
    }
  }

  // logfile

  if (logfile_ctx->enabled == true)
  {
    if (hc_path_exist (logfile_ctx->logfile) == true)
    {
      if (hc_path_is_directory (logfile_ctx->logfile) == true)
      {
        event_log_error (hashcat_ctx, "%s: A directory cannot be used as a logfile argument.", logfile_ctx->logfile);

        return -1;
      }

      if (hc_path_write (logfile_ctx->logfile) == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", logfile_ctx->logfile, strerror (errno));

        return -1;
      }
    }
    else
    {
      if (hc_path_create (logfile_ctx->logfile) == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", logfile_ctx->logfile, strerror (errno));

        return -1;
      }
    }
  }

  // outfile_check

  if (outcheck_ctx->enabled == true)
  {
    if (hc_path_exist (outcheck_ctx->root_directory) == true)
    {
      if (hc_path_is_directory (outcheck_ctx->root_directory) == false)
      {
        event_log_error (hashcat_ctx, "Directory specified in outfile-check '%s' is not a directory.", outcheck_ctx->root_directory);

        return -1;
      }
    }
  }

  // outfile - can be NULL

  if (outfile_ctx->filename != NULL)
  {
    if (hc_path_exist (outfile_ctx->filename) == true)
    {
      if (hc_path_is_directory (outfile_ctx->filename) == true)
      {
        event_log_error (hashcat_ctx, "%s: A directory cannot be used as an outfile.", outfile_ctx->filename);

        return -1;
      }

      if (hc_path_write (outfile_ctx->filename) == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", outfile_ctx->filename, strerror (errno));

        return -1;
      }
    }
    else
    {
      if (hc_path_create (outfile_ctx->filename) == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", outfile_ctx->filename, strerror (errno));

        return -1;
      }
    }
  }

  // check for outfile vs. hashfile

  if (hc_same_files (outfile_ctx->filename, user_options_extra->hc_hash) == true)
  {
    event_log_error (hashcat_ctx, "Outfile and hashfile cannot point to the same file.");

    return -1;
  }

  // check for outfile vs. cached wordlists

  if (user_options->attack_mode == ATTACK_MODE_STRAIGHT)
  {
    for (int i = 0; i < user_options_extra->hc_workc; i++)
    {
      char *wlfile = user_options_extra->hc_workv[i];

      if (hc_same_files (outfile_ctx->filename, wlfile) == true)
      {
        event_log_error (hashcat_ctx, "Outfile and wordlist cannot point to the same file.");

        return -1;
      }
    }
  }
  else if (user_options->attack_mode == ATTACK_MODE_COMBI)
  {
    if (user_options_extra->hc_workc == 2)
    {
      char *dictfile1 = user_options_extra->hc_workv[0];
      char *dictfile2 = user_options_extra->hc_workv[1];

      if (hc_same_files (outfile_ctx->filename, dictfile1) == true)
      {
        event_log_error (hashcat_ctx, "Outfile and wordlist cannot point to the same file.");

        return -1;
      }

      if (hc_same_files (outfile_ctx->filename, dictfile2) == true)
      {
        event_log_error (hashcat_ctx, "Outfile and wordlist cannot point to the same file.");

        return -1;
      }
    }
  }
  else if (user_options->attack_mode == ATTACK_MODE_HYBRID1)
  {
    if (user_options_extra->hc_workc == 2)
    {
      char *wlfile = user_options_extra->hc_workv[0];

      if (hc_same_files (outfile_ctx->filename, wlfile) == true)
      {
        event_log_error (hashcat_ctx, "Outfile and wordlist cannot point to the same file.");

        return -1;
      }
    }
  }
  else if (user_options->attack_mode == ATTACK_MODE_HYBRID2)
  {
    if (user_options_extra->hc_workc == 2)
    {
      char *wlfile = user_options_extra->hc_workv[1];

      if (hc_same_files (outfile_ctx->filename, wlfile) == true)
      {
        event_log_error (hashcat_ctx, "Outfile and wordlist cannot point to the same file.");

        return -1;
      }
    }
  }

  // pidfile

  if (hc_path_exist (pidfile_ctx->filename) == true)
  {
    if (hc_path_is_directory (pidfile_ctx->filename) == true)
    {
      event_log_error (hashcat_ctx, "%s: A directory cannot be used as a pidfile argument.", pidfile_ctx->filename);

      return -1;
    }

    if (hc_path_write (pidfile_ctx->filename) == false)
    {
      event_log_error (hashcat_ctx, "%s: %s", pidfile_ctx->filename, strerror (errno));

      return -1;
    }
  }
  else
  {
    if (hc_path_create (pidfile_ctx->filename) == false)
    {
      event_log_error (hashcat_ctx, "%s: %s", pidfile_ctx->filename, strerror (errno));

      return -1;
    }
  }

  // potfile

  if (potfile_ctx->enabled == true)
  {
    if (hc_path_exist (potfile_ctx->filename) == true)
    {
      if (hc_path_is_directory (potfile_ctx->filename) == true)
      {
        event_log_error (hashcat_ctx, "%s: A directory cannot be used as a potfile argument.", potfile_ctx->filename);

        return -1;
      }

      if (hc_path_write (potfile_ctx->filename) == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", potfile_ctx->filename, strerror (errno));

        return -1;
      }
    }
    else
    {
      if (hc_path_create (potfile_ctx->filename) == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", potfile_ctx->filename, strerror (errno));

        return -1;
      }
    }
  }

  // dictstat

  if (dictstat_ctx->enabled == true)
  {
    if (hc_path_exist (dictstat_ctx->filename) == true)
    {
      if (hc_path_is_directory (dictstat_ctx->filename) == true)
      {
        event_log_error (hashcat_ctx, "%s: A directory cannot be used as a dictstat argument.", dictstat_ctx->filename);

        return -1;
      }

      if (hc_path_write (dictstat_ctx->filename) == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", dictstat_ctx->filename, strerror (errno));

        return -1;
      }
    }
    else
    {
      if (hc_path_create (dictstat_ctx->filename) == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", dictstat_ctx->filename, strerror (errno));

        return -1;
      }
    }
  }

  // single kernel and module existence check to detect "7z e" errors

  char *modulefile = (char *) hcmalloc (HCBUFSIZ_TINY);

  module_filename (folder_config, 0, modulefile, HCBUFSIZ_TINY);

  if (hc_path_exist (modulefile) == false)
  {
    event_log_error (hashcat_ctx, "%s: %s", modulefile, strerror (errno));

    event_log_warning (hashcat_ctx, "If you are using the hashcat binary package this error typically indicates a problem during extraction.");
    event_log_warning (hashcat_ctx, "For example, using \"7z e\" instead of using \"7z x\".");
    event_log_warning (hashcat_ctx, NULL);

    return -1;
  }

  const int rc = hashconfig_init (hashcat_ctx);

  if (rc == -1) return -1;

  hashconfig_destroy (hashcat_ctx);

  hcfree (modulefile);

  // same check but for an OpenCL kernel

  char *kernelfile = (char *) hcmalloc (HCBUFSIZ_TINY);

  generate_source_kernel_filename (false, ATTACK_EXEC_OUTSIDE_KERNEL, ATTACK_KERN_STRAIGHT, 400, 0, folder_config->shared_dir, kernelfile);

  if (hc_path_read (kernelfile) == false)
  {
    event_log_error (hashcat_ctx, "%s: %s", kernelfile, strerror (errno));

    event_log_warning (hashcat_ctx, "If you are using the hashcat binary package this error typically indicates a problem during extraction.");
    event_log_warning (hashcat_ctx, "For example, using \"7z e\" instead of using \"7z x\".");
    event_log_warning (hashcat_ctx, NULL);

    return -1;
  }

  hcfree (kernelfile);

  // loopback - can't check at this point

  // tuning file check already done

  // debugfile check already done

  // dictstat

  if (user_options->keyboard_layout_mapping != NULL)
  {
    if (hc_path_exist (user_options->keyboard_layout_mapping) == true)
    {
      if (hc_path_read (user_options->keyboard_layout_mapping) == false)
      {
        event_log_error (hashcat_ctx, "%s: %s", user_options->keyboard_layout_mapping, strerror (errno));

        return -1;
      }
    }
    else
    {
      event_log_error (hashcat_ctx, "%s: %s", user_options->keyboard_layout_mapping, strerror (errno));

      return -1;
    }
  }

  /**
   * default building options
   */

  if (chdir (folder_config->cpath_real) == -1)
  {
    event_log_error (hashcat_ctx, "%s: %s", folder_config->cpath_real, strerror (errno));

    return -1;
  }

  // include check
  // this test needs to be done manually because of macOS opencl runtime
  // if there's a problem with permission, its not reporting back and erroring out silently

  const char *files_names[] =
  {
    "inc_cipher_aes.cl",
    "inc_cipher_serpent.cl",
    "inc_cipher_twofish.cl",
    "inc_common.cl",
    "inc_comp_multi_bs.cl",
    "inc_comp_multi.cl",
    "inc_comp_single_bs.cl",
    "inc_comp_single.cl",
    "inc_rp_optimized.cl",
    "inc_rp_optimized.h",
    "inc_simd.cl",
    "inc_scalar.cl",
    "inc_types.h",
    "inc_vendor.h",
    NULL
  };

  for (int i = 0; files_names[i] != NULL; i++)
  {
    if (hc_path_read (files_names[i]) == false)
    {
      event_log_error (hashcat_ctx, "%s: %s", files_names[i], strerror (errno));

      return -1;
    }
  }

  // return back to the folder we came from initially (workaround)

  #if defined (_WIN)
  if (chdir ("..") == -1)
  {
    event_log_error (hashcat_ctx, "%s: %s", "..", strerror (errno));

    return -1;
  }
  #else
  if (chdir (folder_config->cwd) == -1)
  {
    event_log_error (hashcat_ctx, "%s: %s", folder_config->cwd, strerror (errno));

    return -1;
  }
  #endif

  return 0;
}