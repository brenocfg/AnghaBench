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
struct TYPE_19__ {int version; int usage; int example_hashes; int opencl_info; } ;
typedef  TYPE_1__ user_options_t ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_20__ {TYPE_1__* user_options; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMPTIME ; 
 char* VERSION_TAG ; 
 int /*<<< orphan*/  event ; 
 int /*<<< orphan*/  example_hashes (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  goodbye_screen (TYPE_2__*,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  hashcat_destroy (TYPE_2__*) ; 
 int hashcat_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashcat_session_destroy (TYPE_2__*) ; 
 int hashcat_session_execute (TYPE_2__*) ; 
 int hashcat_session_init (TYPE_2__*,char const*,char const*,int,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ hcmalloc (int) ; 
 int /*<<< orphan*/  opencl_info (TYPE_2__*) ; 
 int /*<<< orphan*/  opencl_info_compact (TYPE_2__*) ; 
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

  const int rc_hashcat_init = hashcat_init (hashcat_ctx, event);

  if (rc_hashcat_init == -1) return -1;

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

  const int rc_options_init = user_options_init (hashcat_ctx);

  if (rc_options_init == -1) return -1;

  // parse commandline parameters and check them

  const int rc_options_getopt = user_options_getopt (hashcat_ctx, argc, argv);

  if (rc_options_getopt == -1) return -1;

  const int rc_options_sanity = user_options_sanity (hashcat_ctx);

  if (rc_options_sanity == -1) return -1;

  // some early exits

  user_options_t *user_options = hashcat_ctx->user_options;

  #ifdef WITH_BRAIN
  if (user_options->brain_server == true)
  {
    const int rc = brain_server (user_options->brain_host, user_options->brain_port, user_options->brain_password, user_options->brain_session_whitelist);

    return rc;
  }
  #endif

  if (user_options->version == true)
  {
    printf ("%s\n", VERSION_TAG);

    return 0;
  }

  // init a hashcat session; this initializes opencl devices, hwmon, etc

  welcome_screen (hashcat_ctx, VERSION_TAG);

  const int rc_session_init = hashcat_session_init (hashcat_ctx, install_folder, shared_folder, argc, argv, COMPTIME);

  int rc_final = -1;

  if (rc_session_init == 0)
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
    else if (user_options->opencl_info == true)
    {
      // if this is just opencl_info, no need to execute some real cracking session

      opencl_info (hashcat_ctx);

      rc_final = 0;
    }
    else
    {
      // now execute hashcat

      opencl_info_compact (hashcat_ctx);

      user_options_info (hashcat_ctx);

      rc_final = hashcat_session_execute (hashcat_ctx);
    }
  }

  // finish the hashcat session, this shuts down opencl devices, hwmon, etc

  hashcat_session_destroy (hashcat_ctx);

  // finished with hashcat, clean up

  const time_t proc_stop = time (NULL);

  goodbye_screen (hashcat_ctx, proc_start, proc_stop);

  hashcat_destroy (hashcat_ctx);

  free (hashcat_ctx);

  return rc_final;
}