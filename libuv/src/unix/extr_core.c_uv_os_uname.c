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
struct TYPE_3__ {char* sysname; char* release; char* version; char* machine; } ;
typedef  TYPE_1__ uv_utsname_t ;
struct utsname {char* sysname; char* version; char* release; char* machine; } ;

/* Variables and functions */
 int UV_E2BIG ; 
 int UV_EINVAL ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int snprintf (char*,int,char*,char*,char*) ; 
 int uname (struct utsname*) ; 
 int uv__strscpy (char*,char*,int) ; 

int uv_os_uname(uv_utsname_t* buffer) {
  struct utsname buf;
  int r;

  if (buffer == NULL)
    return UV_EINVAL;

  if (uname(&buf) == -1) {
    r = UV__ERR(errno);
    goto error;
  }

  r = uv__strscpy(buffer->sysname, buf.sysname, sizeof(buffer->sysname));
  if (r == UV_E2BIG)
    goto error;

#ifdef _AIX
  r = snprintf(buffer->release,
               sizeof(buffer->release),
               "%s.%s",
               buf.version,
               buf.release);
  if (r >= sizeof(buffer->release)) {
    r = UV_E2BIG;
    goto error;
  }
#else
  r = uv__strscpy(buffer->release, buf.release, sizeof(buffer->release));
  if (r == UV_E2BIG)
    goto error;
#endif

  r = uv__strscpy(buffer->version, buf.version, sizeof(buffer->version));
  if (r == UV_E2BIG)
    goto error;

#if defined(_AIX) || defined(__PASE__)
  r = uv__strscpy(buffer->machine, "ppc64", sizeof(buffer->machine));
#else
  r = uv__strscpy(buffer->machine, buf.machine, sizeof(buffer->machine));
#endif

  if (r == UV_E2BIG)
    goto error;

  return 0;

error:
  buffer->sysname[0] = '\0';
  buffer->release[0] = '\0';
  buffer->version[0] = '\0';
  buffer->machine[0] = '\0';
  return r;
}