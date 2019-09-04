#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* iconfigfile; scalar_t__ load_global_config; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_global_config () ; 
 char* get_home () ; 
 char* realpath (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

char *
get_config_file_path (void)
{
  char *upath = NULL, *rpath = NULL;
  FILE *file;

  /* determine which config file to open, default or custom */
  if (conf.iconfigfile != NULL) {
    rpath = realpath (conf.iconfigfile, NULL);
    if (rpath == NULL)
      FATAL ("Unable to open the specified config file. %s", strerror (errno));
    return rpath;
  }

  /* attempt to use the user's config file */
  upath = get_home ();
  rpath = realpath (upath, NULL);
  if (upath) {
    free (upath);
  }

  /* otherwise, fallback to global config file */
  if ((file = fopen (rpath, "r")) == NULL && conf.load_global_config) {
    upath = get_global_config ();
    rpath = realpath (upath, NULL);
    if (upath) {
      free (upath);
    }
  } else {
    fclose (file);
  }

  return rpath;
}