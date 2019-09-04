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
struct TYPE_27__ {int /*<<< orphan*/  rp_gen_seed; int /*<<< orphan*/  rp_gen_seed_chgd; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_28__ {TYPE_1__* user_options; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int debugfile_init (TYPE_2__*) ; 
 int dictstat_init (TYPE_2__*) ; 
 int event_ctx_init (TYPE_2__*) ; 
 int folder_config_init (TYPE_2__*,char const*,char const*) ; 
 int hwmon_ctx_init (TYPE_2__*) ; 
 int induct_ctx_init (TYPE_2__*) ; 
 int logfile_init (TYPE_2__*) ; 
 int loopback_init (TYPE_2__*) ; 
 int opencl_ctx_devices_init (TYPE_2__*,int const) ; 
 int opencl_ctx_init (TYPE_2__*) ; 
 int outcheck_ctx_init (TYPE_2__*) ; 
 int outfile_init (TYPE_2__*) ; 
 int pidfile_ctx_init (TYPE_2__*) ; 
 int potfile_init (TYPE_2__*) ; 
 int restore_ctx_init (TYPE_2__*,int,char**) ; 
 int set_cpu_affinity (TYPE_2__*) ; 
 int /*<<< orphan*/  setup_environment_variables () ; 
 int /*<<< orphan*/  setup_seeding (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_umask () ; 
 int status_ctx_init (TYPE_2__*) ; 
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

  const int rc_event_init = event_ctx_init (hashcat_ctx);

  if (rc_event_init == -1) return -1;

  /**
   * status init
   */

  const int rc_status_init = status_ctx_init (hashcat_ctx);

  if (rc_status_init == -1) return -1;

  /**
   * folder
   */

  const int rc_folder_config_init = folder_config_init (hashcat_ctx, install_folder, shared_folder);

  if (rc_folder_config_init == -1) return -1;

  /**
   * pidfile
   */

  const int rc_pidfile_init = pidfile_ctx_init (hashcat_ctx);

  if (rc_pidfile_init == -1) return -1;

  /**
   * restore
   */

  const int rc_restore_init = restore_ctx_init (hashcat_ctx, argc, argv);

  if (rc_restore_init == -1) return -1;

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

    const int iResult = WSAStartup (wVersionRequested, &wsaData);

    if (iResult != NO_ERROR)
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

  const int rc_logfile_init = logfile_init (hashcat_ctx);

  if (rc_logfile_init == -1) return -1;

  /**
   * cpu affinity
   */

  const int rc_affinity = set_cpu_affinity (hashcat_ctx);

  if (rc_affinity == -1) return -1;

  /**
   * prepare seeding for random number generator, required by logfile and rules generator
   */

  setup_seeding (user_options->rp_gen_seed_chgd, user_options->rp_gen_seed);

  /**
   * To help users a bit
   */

  setup_environment_variables ();

  setup_umask ();

  /**
   * tuning db
   */

  const int rc_tuning_db = tuning_db_init (hashcat_ctx);

  if (rc_tuning_db == -1) return -1;

  /**
   * induction directory
   */

  const int rc_induct_ctx_init = induct_ctx_init (hashcat_ctx);

  if (rc_induct_ctx_init == -1) return -1;

  /**
   * outfile-check directory
   */

  const int rc_outcheck_ctx_init = outcheck_ctx_init (hashcat_ctx);

  if (rc_outcheck_ctx_init == -1) return -1;

  /**
   * outfile itself
   */

  const int rc_outfile_init = outfile_init (hashcat_ctx);

  if (rc_outfile_init == -1) return -1;

  /**
   * potfile init
   * this is only setting path because potfile can be used in read and write mode depending on user options
   * plus it depends on hash_mode, so we continue using it in outer_loop
   */

  const int rc_potfile_init = potfile_init (hashcat_ctx);

  if (rc_potfile_init == -1) return -1;

  /**
   * dictstat init
   */

  const int rc_dictstat_init = dictstat_init (hashcat_ctx);

  if (rc_dictstat_init == -1) return -1;

  /**
   * loopback init
   */

  const int rc_loopback_init = loopback_init (hashcat_ctx);

  if (rc_loopback_init == -1) return -1;

  /**
   * debugfile init
   */

  const int rc_debugfile_init = debugfile_init (hashcat_ctx);

  if (rc_debugfile_init == -1) return -1;

  /**
   * Try to detect if all the files we're going to use are accessible in the mode we want them
   */

  const int rc_user_options_check_files = user_options_check_files (hashcat_ctx);

  if (rc_user_options_check_files == -1) return -1;

  /**
   * Init OpenCL library loader
   */

  const int rc_opencl_init = opencl_ctx_init (hashcat_ctx);

  if (rc_opencl_init == -1) return -1;

  /**
   * Init OpenCL devices
   */

  const int rc_devices_init = opencl_ctx_devices_init (hashcat_ctx, comptime);

  if (rc_devices_init == -1) return -1;

  /**
   * HM devices: init
   */

  const int rc_hwmon_init = hwmon_ctx_init (hashcat_ctx);

  if (rc_hwmon_init == -1) return -1;

  // done

  return 0;
}