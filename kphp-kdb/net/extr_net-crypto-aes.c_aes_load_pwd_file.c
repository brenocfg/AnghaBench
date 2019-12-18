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
 char const* DEFAULT_PWD_FILE ; 
 int MAX_PWD_LEN ; 
 int MIN_PWD_LEN ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int aes_initialized ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 long lrand48 () ; 
 int open (char const*,int) ; 
 scalar_t__ pwd_buf ; 
 int pwd_len ; 
 scalar_t__ rand_buf ; 
 int read (int,scalar_t__,int) ; 
 int /*<<< orphan*/  srand48 (long) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int aes_load_pwd_file (const char *filename) {
  int h = open ("/dev/random", O_RDONLY | O_NONBLOCK);
  int r = 0;

  if (h >= 0) {
    r = read (h, rand_buf, 16);
    if (r > 0 && verbosity > 1) {
      fprintf (stderr, "added %d bytes of real entropy to the AES security key\n", r);
    }
    close (h);
  }

  if (r < 16) {
    h = open ("/dev/urandom", O_RDONLY);
    if (h < 0) {
      pwd_len = 0;
      return -1;
    }
    int s = read (h, rand_buf + r, 16 - r);
    if (r + s != 16) {
      pwd_len = 0;
      return -1;
    }
    close (h);
  }

  *(long *) rand_buf ^= lrand48();

  srand48 (*(long *)rand_buf);

  h = open (filename ? filename : DEFAULT_PWD_FILE, O_RDONLY);
  if (h < 0) {
    return -1;
  }

  r = read (h, pwd_buf, MAX_PWD_LEN + 1);

  close (h);

  if (r < MIN_PWD_LEN || r > MAX_PWD_LEN) {
    return -1;
  }

  pwd_len = r;

  if (verbosity > 0) {
    fprintf (stderr, "loaded password file %s\n", filename ? filename : DEFAULT_PWD_FILE);
  }

  aes_initialized = 1;

  return 1;
}