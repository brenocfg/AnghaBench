#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ debug_log; scalar_t__ invalid_requests_log; int /*<<< orphan*/  output_stdout; scalar_t__ list_agents; } ;
struct TYPE_8__ {scalar_t__ pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (char*) ; 
 TYPE_7__ conf ; 
 scalar_t__ dash ; 
 int /*<<< orphan*/  dbg_log_close () ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_agent_list () ; 
 int /*<<< orphan*/  free_browsers_hash () ; 
 int /*<<< orphan*/  free_cmd_args () ; 
 int /*<<< orphan*/  free_color_lists () ; 
 int /*<<< orphan*/  free_dashboard (scalar_t__) ; 
 int /*<<< orphan*/  free_formats () ; 
 int /*<<< orphan*/  free_logerrors (TYPE_1__*) ; 
 int /*<<< orphan*/  geoip_free () ; 
 TYPE_1__* glog ; 
 TYPE_1__* gwsreader ; 
 TYPE_1__* gwswriter ; 
 int /*<<< orphan*/  house_keeping_holder () ; 
 int /*<<< orphan*/  invalid_log_close () ; 
 TYPE_1__* parsing_spinner ; 
 int /*<<< orphan*/  reset_find () ; 

__attribute__((used)) static void
house_keeping (void)
{
#ifdef TCB_MEMHASH
  /* free malloc'd int values on the agent list */
  if (conf.list_agents)
    free_agent_list ();
#endif

  house_keeping_holder ();

  /* DASHBOARD */
  if (dash && !conf.output_stdout) {
    free_dashboard (dash);
    reset_find ();
  }

  /* GEOLOCATION */
#ifdef HAVE_GEOLOCATION
  geoip_free ();
#endif

  /* LOGGER */
  if (glog->pipe)
    fclose (glog->pipe);
  free_logerrors (glog);
  free (glog);

  /* INVALID REQUESTS */
  if (conf.invalid_requests_log) {
    LOG_DEBUG (("Closing invalid requests log.\n"));
    invalid_log_close ();
  }

  /* CONFIGURATION */
  free_formats ();
  free_browsers_hash ();
  if (conf.debug_log) {
    LOG_DEBUG (("Bye.\n"));
    dbg_log_close ();
  }

  /* clear spinner */
  free (parsing_spinner);
  /* free colors */
  free_color_lists ();
  /* free cmd arguments */
  free_cmd_args ();
  /* WebSocket writer */
  free (gwswriter);
  /* WebSocket reader */
  free (gwsreader);
}