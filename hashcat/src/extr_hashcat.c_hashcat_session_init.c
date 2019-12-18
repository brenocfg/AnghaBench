#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {int brain_client; int /*<<< orphan*/  rp_gen_seed; int /*<<< orphan*/  rp_gen_seed_chgd; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_28__ {int /*<<< orphan*/  folder_config; TYPE_1__* user_options; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
typedef  int /*<<< orphan*/  WSADATA ;
typedef  int /*<<< orphan*/  WORD ;

/* Variables and functions */
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 scalar_t__ NO_ERROR ; 
 scalar_t__ WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int backend_ctx_devices_init (TYPE_2__*,int const) ; 
 int backend_ctx_init (TYPE_2__*) ; 
 int debugfile_init (TYPE_2__*) ; 
 int dictstat_init (TYPE_2__*) ; 
 int /*<<< orphan*/  errno ; 
 int event_ctx_init (TYPE_2__*) ; 
 int folder_config_init (TYPE_2__*,char const*,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int hwmon_ctx_init (TYPE_2__*) ; 
 int induct_ctx_init (TYPE_2__*) ; 
 int logfile_init (TYPE_2__*) ; 
 int loopback_init (TYPE_2__*) ; 
 int outcheck_ctx_init (TYPE_2__*) ; 
 int outfile_init (TYPE_2__*) ; 
 int pidfile_ctx_init (TYPE_2__*) ; 
 int potfile_init (TYPE_2__*) ; 
 int restore_ctx_init (TYPE_2__*,int,char**) ; 
 int set_cpu_affinity (TYPE_2__*) ; 
 int /*<<< orphan*/  setup_environment_variables (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_seeding (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_umask () ; 
 int status_ctx_init (TYPE_2__*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int tuning_db_init (TYPE_2__*) ; 
 int user_options_check_files (TYPE_2__*) ; 
 int /*<<< orphan*/  user_options_extra_init (TYPE_2__*) ; 
 int /*<<< orphan*/  user_options_postprocess (TYPE_2__*) ; 
 int /*<<< orphan*/  user_options_preprocess (TYPE_2__*) ; 
 int /*<<< orphan*/  user_options_session_auto (TYPE_2__*) ; 

int hashcat_session_init (hashcat_ctx_t *hashcat_ctx, const char *install_folder, const char *shared_folder, int argc, char **argv, const int comptime)
{
  user_options_t *user_options = hashcat_ctx->user_options;

  /**
   * make it a bit more comfortable to use some of the special modes in hashcat
   */

  user_options_session_auto (hashcat_ctx);

  /**
   * event init (needed for logging so should be first)
   */

  if (event_ctx_init (hashcat_ctx) == -1) return -1;

  /**
   * status init
   */

  if (status_ctx_init (hashcat_ctx) == -1) return -1;

  /**
   * folder
   */

  if (folder_config_init (hashcat_ctx, install_folder, shared_folder) == -1) return -1;

  /**
   * pidfile
   */

  if (pidfile_ctx_init (hashcat_ctx) == -1) return -1;

  /**
   * restore
   */

  if (restore_ctx_init (hashcat_ctx, argc, argv) == -1) return -1;

  /**
   * process user input
   */

  user_options_preprocess (hashcat_ctx);

  user_options_extra_init (hashcat_ctx);

  user_options_postprocess (hashcat_ctx);

  /**
   * windows and sockets...
   */

  #ifdef WITH_BRAIN
  #if defined (_WIN)
  if (user_options->brain_client == true)
  {
    WSADATA wsaData;

    WORD wVersionRequested = MAKEWORD (2,2);

    if (WSAStartup (wVersionRequested, &wsaData) != NO_ERROR)
    {
      fprintf (stderr, "WSAStartup: %s\n", strerror (errno));

      return -1;
    }
  }
  #endif
  #endif

  /**
   * logfile
   */

  if (logfile_init (hashcat_ctx) == -1) return -1;

  /**
   * cpu affinity
   */

  if (set_cpu_affinity (hashcat_ctx) == -1) return -1;

  /**
   * prepare seeding for random number generator, required by logfile and rules generator
   */

  setup_seeding (user_options->rp_gen_seed_chgd, user_options->rp_gen_seed);

  /**
   * To help users a bit
   */

  setup_environment_variables (hashcat_ctx->folder_config);

  setup_umask ();

  /**
   * tuning db
   */

  if (tuning_db_init (hashcat_ctx) == -1) return -1;

  /**
   * induction directory
   */

  if (induct_ctx_init (hashcat_ctx) == -1) return -1;

  /**
   * outfile-check directory
   */

  if (outcheck_ctx_init (hashcat_ctx) == -1) return -1;

  /**
   * outfile itself
   */

  if (outfile_init (hashcat_ctx) == -1) return -1;

  /**
   * potfile init
   * this is only setting path because potfile can be used in read and write mode depending on user options
   * plus it depends on hash_mode, so we continue using it in outer_loop
   */

  if (potfile_init (hashcat_ctx) == -1) return -1;

  /**
   * dictstat init
   */

  if (dictstat_init (hashcat_ctx) == -1) return -1;

  /**
   * loopback init
   */

  if (loopback_init (hashcat_ctx) == -1) return -1;

  /**
   * debugfile init
   */

  if (debugfile_init (hashcat_ctx) == -1) return -1;

  /**
   * Try to detect if all the files we're going to use are accessible in the mode we want them
   */

  if (user_options_check_files (hashcat_ctx) == -1) return -1;

  /**
   * Init backend library loader
   */

  if (backend_ctx_init (hashcat_ctx) == -1) return -1;

  /**
   * Init backend devices
   */

  if (backend_ctx_devices_init (hashcat_ctx, comptime) == -1) return -1;

  /**
   * HM devices: init
   */

  if (hwmon_ctx_init (hashcat_ctx) == -1) return -1;

  // done

  return 0;
}