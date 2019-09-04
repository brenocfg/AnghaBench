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
typedef  int /*<<< orphan*/  trypath ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int PATH_MAX ; 
 int UV_EINVAL ; 
 int UV_ENOMEM ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 char* getenv (char*) ; 
 int getexe (int,char*,int) ; 
 int getpid () ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 char* realpath (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 size_t strlen (char*) ; 
 char* strtok (char*,char*) ; 
 int /*<<< orphan*/  uv__free (char*) ; 
 char* uv__strdup (char*) ; 

int uv_exepath(char* buffer, size_t* size) {
  int res;
  char args[PATH_MAX];
  char abspath[PATH_MAX];
  size_t abspath_size;
  int pid;

  if (buffer == NULL || size == NULL || *size == 0)
    return UV_EINVAL;

  pid = getpid();
  res = getexe(pid, args, sizeof(args));
  if (res < 0)
    return UV_EINVAL;

  /*
   * Possibilities for args:
   * i) an absolute path such as: /home/user/myprojects/nodejs/node
   * ii) a relative path such as: ./node or ../myprojects/nodejs/node
   * iii) a bare filename such as "node", after exporting PATH variable
   *     to its location.
   */

  /* Case i) and ii) absolute or relative paths */
  if (strchr(args, '/') != NULL) {
    if (realpath(args, abspath) != abspath)
      return UV__ERR(errno);

    abspath_size = strlen(abspath);

    *size -= 1;
    if (*size > abspath_size)
      *size = abspath_size;

    memcpy(buffer, abspath, *size);
    buffer[*size] = '\0';

    return 0;
  } else {
    /* Case iii). Search PATH environment variable */
    char trypath[PATH_MAX];
    char* clonedpath = NULL;
    char* token = NULL;
    char* path = getenv("PATH");

    if (path == NULL)
      return UV_EINVAL;

    clonedpath = uv__strdup(path);
    if (clonedpath == NULL)
      return UV_ENOMEM;

    token = strtok(clonedpath, ":");
    while (token != NULL) {
      snprintf(trypath, sizeof(trypath) - 1, "%s/%s", token, args);
      if (realpath(trypath, abspath) == abspath) {
        /* Check the match is executable */
        if (access(abspath, X_OK) == 0) {
          abspath_size = strlen(abspath);

          *size -= 1;
          if (*size > abspath_size)
            *size = abspath_size;

          memcpy(buffer, abspath, *size);
          buffer[*size] = '\0';

          uv__free(clonedpath);
          return 0;
        }
      }
      token = strtok(NULL, ":");
    }
    uv__free(clonedpath);

    /* Out of tokens (path entries), and no match found */
    return UV_EINVAL;
  }
}