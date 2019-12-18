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
 int /*<<< orphan*/  free (char*) ; 
 int sm_connect_tcp (char*,int) ; 
 int sm_connect_unix (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char* strndup (char const*,size_t) ; 
 char* strrchr (char const*,char) ; 
 int strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sm_connect(const char *socket_addr) {
  if (strncmp(socket_addr, "unix:", 5) == 0) {
#ifdef WIN32
    return -1;
#else
    return sm_connect_unix(socket_addr + 5);
#endif
  } else {
    const char *s_port = strrchr(socket_addr, ':');
    int port = 0;

    if (s_port) {
      port = strtol(s_port + 1, NULL, 0);
    }

    if (port <= 0) {
      return -1;
    }

    size_t host_len = s_port - socket_addr;
    char *host = strndup(socket_addr, host_len);

    int ret = sm_connect_tcp(host, port);
    free(host);
    return ret;
  }
}