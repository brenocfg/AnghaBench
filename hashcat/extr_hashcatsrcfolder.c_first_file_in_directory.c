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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 char* strdup (char*) ; 

char *first_file_in_directory (const char *path)
{
  DIR *d;

  if ((d = opendir (path)) != NULL)
  {
    char *first_file = NULL;

    #if 0

    struct dirent e;

    for (;;)
    {
      memset (&e, 0, sizeof (e));

      struct dirent *de = NULL;

      if (readdir_r (d, &e, &de) != 0) break;

      if (de == NULL) break;

    #else

    struct dirent *de;

    while ((de = readdir (d)) != NULL)
    {

    #endif

      if (de->d_name[0] == '.') continue;

      first_file = strdup (de->d_name);

      break;
    }

    closedir (d);

    return first_file;
  }

  return NULL;
}