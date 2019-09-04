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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  ENOMEM ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int readlink (char const*,char*,size_t) ; 
 int /*<<< orphan*/ * realpath (char*,char*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  uv__free (char*) ; 
 char* uv__malloc (size_t) ; 

ssize_t os390_readlink(const char* path, char* buf, size_t len) {
  ssize_t rlen;
  ssize_t vlen;
  ssize_t plen;
  char* delimiter;
  char old_delim;
  char* tmpbuf;
  char realpathstr[PATH_MAX + 1];

  tmpbuf = uv__malloc(len + 1);
  if (tmpbuf == NULL) {
    errno = ENOMEM;
    return -1;
  }

  rlen = readlink(path, tmpbuf, len);
  if (rlen < 0) {
    uv__free(tmpbuf);
    return rlen;
  }

  if (rlen < 3 || strncmp("/$", tmpbuf, 2) != 0) {
    /* Straightforward readlink. */
    memcpy(buf, tmpbuf, rlen);
    uv__free(tmpbuf);
    return rlen;
  }

  /*
   * There is a parmlib variable at the beginning
   * which needs interpretation.
   */
  tmpbuf[rlen] = '\0';
  delimiter = strchr(tmpbuf + 2, '/');
  if (delimiter == NULL)
    /* No slash at the end */
    delimiter = strchr(tmpbuf + 2, '\0');

  /* Read real path of the variable. */
  old_delim = *delimiter;
  *delimiter = '\0';
  if (realpath(tmpbuf, realpathstr) == NULL) {
    uv__free(tmpbuf);
    return -1;
  }

  /* realpathstr is not guaranteed to end with null byte.*/
  realpathstr[PATH_MAX] = '\0';

  /* Reset the delimiter and fill up the buffer. */
  *delimiter = old_delim;
  plen = strlen(delimiter);
  vlen = strlen(realpathstr);
  rlen = plen + vlen;
  if (rlen > len) {
    uv__free(tmpbuf);
    errno = ENAMETOOLONG;
    return -1;
  }
  memcpy(buf, realpathstr, vlen);
  memcpy(buf + vlen, delimiter, plen);

  /* Done using temporary buffer. */
  uv__free(tmpbuf);

  return rlen;
}