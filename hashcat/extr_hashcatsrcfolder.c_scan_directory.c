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
 scalar_t__ ENOTDIR ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  hc_asprintf (char**,char*,char*,char*) ; 
 int /*<<< orphan*/  hcfree (char*) ; 
 scalar_t__ hcrealloc (char**,size_t,int) ; 
 char* hcstrdup (char const*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 size_t strlen (char*) ; 

char **scan_directory (const char *path)
{
  char *tmp_path = hcstrdup (path);

  size_t tmp_path_len = strlen (tmp_path);

  while (tmp_path[tmp_path_len - 1] == '/' || tmp_path[tmp_path_len - 1] == '\\')
  {
    tmp_path[tmp_path_len - 1] = 0;

    tmp_path_len = strlen (tmp_path);
  }

  char **files = NULL;

  size_t num_files = 0;

  DIR *d = NULL;

  if ((d = opendir (tmp_path)) != NULL)
  {
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

      char *path_file;

      hc_asprintf (&path_file, "%s/%s", tmp_path, de->d_name);

      DIR *d_test;

      if ((d_test = opendir (path_file)) != NULL)
      {
        closedir (d_test);

        hcfree (path_file);
      }
      else
      {
        files = (char **) hcrealloc (files, (num_files + 1) * sizeof (char *), sizeof (char *));

        files[num_files] = path_file;

        num_files++;
      }
    }

    closedir (d);
  }
  else if (errno == ENOTDIR)
  {
    files = (char **) hcrealloc (files, (num_files + 1) * sizeof (char *), sizeof (char *));

    files[num_files] = hcstrdup (path);

    num_files++;
  }

  files = (char **) hcrealloc (files, (num_files + 1) * sizeof (char *), sizeof (char *));

  files[num_files] = NULL;

  hcfree (tmp_path);

  return (files);
}