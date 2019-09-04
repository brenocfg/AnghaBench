#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  debugfile_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictstat_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_ctx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  folder_config_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_ctx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  induct_ctx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logfile_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loopback_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opencl_ctx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opencl_ctx_devices_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outcheck_ctx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outfile_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pidfile_ctx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  potfile_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restore_ctx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  status_ctx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuning_db_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_options_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_options_extra_destroy (int /*<<< orphan*/ *) ; 

int hashcat_session_destroy (hashcat_ctx_t *hashcat_ctx)
{
  #ifdef WITH_BRAIN
  #if defined (_WIN)
  user_options_t *user_options = hashcat_ctx->user_options;

  if (user_options->brain_client == true)
  {
    WSACleanup();
  }
  #endif
  #endif

  debugfile_destroy          (hashcat_ctx);
  dictstat_destroy           (hashcat_ctx);
  folder_config_destroy      (hashcat_ctx);
  hwmon_ctx_destroy          (hashcat_ctx);
  induct_ctx_destroy         (hashcat_ctx);
  logfile_destroy            (hashcat_ctx);
  loopback_destroy           (hashcat_ctx);
  opencl_ctx_devices_destroy (hashcat_ctx);
  opencl_ctx_destroy         (hashcat_ctx);
  outcheck_ctx_destroy       (hashcat_ctx);
  outfile_destroy            (hashcat_ctx);
  pidfile_ctx_destroy        (hashcat_ctx);
  potfile_destroy            (hashcat_ctx);
  restore_ctx_destroy        (hashcat_ctx);
  tuning_db_destroy          (hashcat_ctx);
  user_options_destroy       (hashcat_ctx);
  user_options_extra_destroy (hashcat_ctx);
  status_ctx_destroy         (hashcat_ctx);
  event_ctx_destroy          (hashcat_ctx);

  return 0;
}