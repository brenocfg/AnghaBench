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
typedef  int pid_t ;

/* Variables and functions */
 int CTL_KERN ; 
 scalar_t__ ENOMEM ; 
 int KERN_PROC_ARGS ; 
 int KERN_PROC_ARGV ; 
 int UV_EINVAL ; 
 int UV_ENOMEM ; 
 int UV__ERR (scalar_t__) ; 
 scalar_t__ errno ; 
 int getpid () ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 size_t strlen (char*) ; 
 scalar_t__ sysctl (int*,int,char**,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__free (char**) ; 
 char** uv__realloc (char**,size_t) ; 

int uv_exepath(char* buffer, size_t* size) {
  int mib[4];
  char **argsbuf = NULL;
  char **argsbuf_tmp;
  size_t argsbuf_size = 100U;
  size_t exepath_size;
  pid_t mypid;
  int err;

  if (buffer == NULL || size == NULL || *size == 0)
    return UV_EINVAL;

  mypid = getpid();
  for (;;) {
    err = UV_ENOMEM;
    argsbuf_tmp = uv__realloc(argsbuf, argsbuf_size);
    if (argsbuf_tmp == NULL)
      goto out;
    argsbuf = argsbuf_tmp;
    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC_ARGS;
    mib[2] = mypid;
    mib[3] = KERN_PROC_ARGV;
    if (sysctl(mib, 4, argsbuf, &argsbuf_size, NULL, 0) == 0) {
      break;
    }
    if (errno != ENOMEM) {
      err = UV__ERR(errno);
      goto out;
    }
    argsbuf_size *= 2U;
  }

  if (argsbuf[0] == NULL) {
    err = UV_EINVAL;  /* FIXME(bnoordhuis) More appropriate error. */
    goto out;
  }

  *size -= 1;
  exepath_size = strlen(argsbuf[0]);
  if (*size > exepath_size)
    *size = exepath_size;

  memcpy(buffer, argsbuf[0], *size);
  buffer[*size] = '\0';
  err = 0;

out:
  uv__free(argsbuf);

  return err;
}