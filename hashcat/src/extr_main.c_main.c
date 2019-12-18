#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int brain_server; int version; int usage; int example_hashes; int backend_info; int /*<<< orphan*/  brain_session_whitelist; int /*<<< orphan*/  brain_password; int /*<<< orphan*/  brain_port; int /*<<< orphan*/  brain_host; } ;
typedef  TYPE_1__ user_options_t ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_20__ {TYPE_1__* user_options; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMPTIME ; 
 char* INSTALL_FOLDER ; 
 char* SHARED_FOLDER ; 
 char* VERSION_TAG ; 
 int /*<<< orphan*/  backend_info (TYPE_2__*) ; 
 int /*<<< orphan*/  backend_info_compact (TYPE_2__*) ; 
 int brain_server (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event ; 
 int /*<<< orphan*/  example_hashes (TYPE_2__*) ; 
 int /*<<< orphan*/  goodbye_screen (TYPE_2__*,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  hashcat_destroy (TYPE_2__*) ; 
 int hashcat_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashcat_session_destroy (TYPE_2__*) ; 
 int hashcat_session_execute (TYPE_2__*) ; 
 scalar_t__ hashcat_session_init (TYPE_2__*,char const*,char const*,int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hcfree (TYPE_2__*) ; 
 scalar_t__ hcmalloc (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  setup_console () ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage_big_print (TYPE_2__*) ; 
 int user_options_getopt (TYPE_2__*,int,char**) ; 
 int /*<<< orphan*/  user_options_info (TYPE_2__*) ; 
 int user_options_init (TYPE_2__*) ; 
 int user_options_sanity (TYPE_2__*) ; 
 int /*<<< orphan*/  welcome_screen (TYPE_2__*,char*) ; 

int main (int argc, char **argv)
{
  // this increases the size on windows dos boxes

  setup_console ();

  const time_t proc_start = time (NULL);

  // hashcat main context

  hashcat_ctx_t *hashcat_ctx = (hashcat_ctx_t *) hcmalloc (sizeof (hashcat_ctx_t));

  if (hashcat_init (hashcat_ctx, event) == -1)
  {
    hcfree (hashcat_ctx);

    return -1;
  }
  // install and shared folder need to be set to recognize "make install" use

  const char *install_folder = NULL;
  const char *shared_folder  = NULL;

  #if defined (INSTALL_FOLDER)
  install_folder = INSTALL_FOLDER;
  #endif

  #if defined (SHARED_FOLDER)
  shared_folder = SHARED_FOLDER;
  #endif

  // initialize the user options with some defaults (you can override them later)

  if (user_options_init (hashcat_ctx) == -1)
  {
    hcfree (hashcat_ctx);

    return -1;
  }

  // parse commandline parameters and check them

  if (user_options_getopt (hashcat_ctx, argc, argv) == -1)
  {
    hcfree (hashcat_ctx);

    return -1;
  }

  if (user_options_sanity (hashcat_ctx) == -1)
  {
    hcfree (hashcat_ctx);

    return -1;
  }

  // some early exits

  user_options_t *user_options = hashcat_ctx->user_options;

  #ifdef WITH_BRAIN
  if (user_options->brain_server == true)
  {
    const int rc = brain_server (user_options->brain_host, user_options->brain_port, user_options->brain_password, user_options->brain_session_whitelist);

    hcfree (hashcat_ctx);

    return rc;
  }
  #endif

  if (user_options->version == true)
  {
    printf ("%s\n", VERSION_TAG);

    hcfree (hashcat_ctx);

    return 0;
  }

  // init a hashcat session; this initializes backend devices, hwmon, etc

  welcome_screen (hashcat_ctx, VERSION_TAG);

  int rc_final = -1;

  if (hashcat_session_init (hashcat_ctx, install_folder, shared_folder, argc, argv, COMPTIME) == 0)
  {
    if (user_options->usage == true)
    {
      usage_big_print (hashcat_ctx);

      rc_final = 0;
    }
    else if (user_options->example_hashes == true)
    {
      example_hashes (hashcat_ctx);

      rc_final = 0;
    }
    else if (user_options->backend_info == true)
    {
      // if this is just backend_info, no need to execute some real cracking session

      backend_info (hashcat_ctx);

      rc_final = 0;
    }
    else
    {
      // now execute hashcat

      backend_info_compact (hashcat_ctx);

      user_options_info (hashcat_ctx);

      rc_final = hashcat_session_execute (hashcat_ctx);
    }
  }

  // finish the hashcat session, this shuts down backend devices, hwmon, etc

  hashcat_session_destroy (hashcat_ctx);

  // finished with hashcat, clean up

  const time_t proc_stop = time (NULL);

  goodbye_screen (hashcat_ctx, proc_start, proc_stop);

  hashcat_destroy (hashcat_ctx);

  hcfree (hashcat_ctx);

  return rc_final;
}