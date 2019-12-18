#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int brain_client; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_24__ {TYPE_1__* user_options; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  WSACleanup () ; 
 int /*<<< orphan*/  backend_ctx_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  backend_ctx_devices_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  debugfile_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  dictstat_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  event_ctx_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  folder_config_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  hwmon_ctx_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  induct_ctx_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  logfile_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  loopback_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  outcheck_ctx_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  outfile_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  pidfile_ctx_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  potfile_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  restore_ctx_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  status_ctx_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  tuning_db_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  user_options_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  user_options_extra_destroy (TYPE_2__*) ; 

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

  debugfile_destroy           (hashcat_ctx);
  dictstat_destroy            (hashcat_ctx);
  folder_config_destroy       (hashcat_ctx);
  hwmon_ctx_destroy           (hashcat_ctx);
  induct_ctx_destroy          (hashcat_ctx);
  logfile_destroy             (hashcat_ctx);
  loopback_destroy            (hashcat_ctx);
  backend_ctx_devices_destroy (hashcat_ctx);
  backend_ctx_destroy         (hashcat_ctx);
  outcheck_ctx_destroy        (hashcat_ctx);
  outfile_destroy             (hashcat_ctx);
  pidfile_ctx_destroy         (hashcat_ctx);
  potfile_destroy             (hashcat_ctx);
  restore_ctx_destroy         (hashcat_ctx);
  tuning_db_destroy           (hashcat_ctx);
  user_options_destroy        (hashcat_ctx);
  user_options_extra_destroy  (hashcat_ctx);
  status_ctx_destroy          (hashcat_ctx);
  event_ctx_destroy           (hashcat_ctx);

  return 0;
}