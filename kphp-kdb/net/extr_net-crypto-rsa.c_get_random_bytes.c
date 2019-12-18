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
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int) ; 
 int read (int,void*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

int get_random_bytes (void *buf, int n) {
  int r = 0, h = open ("/dev/random", O_RDONLY | O_NONBLOCK);
  if (h >= 0) {
    r = read (h, buf, n);
    if (r > 0) {
      vkprintf (3, "added %d bytes of real entropy to the security key\n", r);
    }
    close (h);
  }

  if (r < n) {
    h = open ("/dev/urandom", O_RDONLY);
    if (h < 0) {
      return r;
    }
    int s = read (h, buf + r, n - r);
    close (h);
    if (s < 0) {
      return r;
    }
    r += s;
  }
  return r;
}