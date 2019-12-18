#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* profile_dir; } ;
typedef  TYPE_1__ folder_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  CW_SYNC_WINENV ; 
 int /*<<< orphan*/  cygwin_internal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  hc_asprintf (char**,char*,char*) ; 
 int /*<<< orphan*/  putenv (char*) ; 

void setup_environment_variables (const folder_config_t *folder_config)
{
  char *compute = getenv ("COMPUTE");

  if (compute)
  {
    char *display;

    hc_asprintf (&display, "DISPLAY=%s", compute);

    putenv (display);

    free (display);
  }
  else
  {
    if (getenv ("DISPLAY") == NULL)
      putenv ((char *) "DISPLAY=:0");
  }

  /*
  if (getenv ("OCL_CODE_CACHE_ENABLE") == NULL)
    putenv ((char *) "OCL_CODE_CACHE_ENABLE=0");

  if (getenv ("CUDA_CACHE_DISABLE") == NULL)
    putenv ((char *) "CUDA_CACHE_DISABLE=1");

  if (getenv ("POCL_KERNEL_CACHE") == NULL)
    putenv ((char *) "POCL_KERNEL_CACHE=0");
  */

  if (getenv ("TMPDIR") == NULL)
  {
    char *tmpdir = NULL;

    hc_asprintf (&tmpdir, "TMPDIR=%s", folder_config->profile_dir);

    putenv (tmpdir);

    // we can't free tmpdir at this point!
  }

  if (getenv ("CL_CONFIG_USE_VECTORIZER") == NULL)
    putenv ((char *) "CL_CONFIG_USE_VECTORIZER=False");

  #if defined (__CYGWIN__)
  cygwin_internal (CW_SYNC_WINENV);
  #endif
}