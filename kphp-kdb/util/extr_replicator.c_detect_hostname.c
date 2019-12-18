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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int* getenv (char*) ; 
 int* hostname ; 
 int* hostname_buffer ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,int*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

int detect_hostname (void) {
  int r, i;
  if (!hostname || !*hostname) {
    hostname = getenv ("HOSTNAME");
    if (!hostname || !*hostname) {
      int fd = open ("/etc/hostname", O_RDONLY);
      if (fd < 0) {
        fprintf (stderr, "cannot read /etc/hostname: %m\n");
        exit (2);
      }
      r = read (fd, hostname_buffer, 256);
      if (r <= 0 || r >= 256) {
        fprintf (stderr, "cannot read hostname from /etc/hostname: %d bytes read\n", r);
        exit (2);
      }
      hostname_buffer[r] = 0;
      close (fd);
      hostname = hostname_buffer;
      while (*hostname == 9 || *hostname == 32) {
        hostname++;
      }
      i = 0;
      while (hostname[i] > 32) {
        i++;
      }
      hostname[i] = 0;
    }
  }
  if (!hostname || !*hostname) {
    fprintf (stderr, "fatal: cannot detect hostname\n");
    exit (2);
  }
  i = 0;
  while ((hostname[i] >= '0' && hostname[i] <= '9') || hostname[i] == '.' || hostname[i] == '-' || hostname[i] == '_' || (hostname[i] >= 'A' && hostname[i] <= 'Z') || (hostname[i] >= 'a' && hostname[i] <= 'z')) {
    i++;
  }
  if (hostname[i] || i >= 64) {
    fprintf (stderr, "fatal: bad hostname '%s'\n", hostname);
    exit (2);
  }
  if (verbosity > 0) {
    fprintf (stderr, "hostname is %s\n", hostname);
  }
  return 0;
}