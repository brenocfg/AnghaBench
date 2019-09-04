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

/* Variables and functions */
 char* ERR_NODEF_CONF_FILE ; 
 char* ERR_NODEF_CONF_FILE_DESC ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_config_file_path () ; 
 int /*<<< orphan*/  stdout ; 

void
display_default_config_file (void)
{
  char *path = get_config_file_path ();

  if (!path) {
    fprintf (stdout, "%s\n", ERR_NODEF_CONF_FILE);
    fprintf (stdout, "%s `-p /path/goaccess.conf`\n", ERR_NODEF_CONF_FILE_DESC);
  } else {
    fprintf (stdout, "%s\n", path);
    free (path);
  }
}