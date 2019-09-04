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
struct timespec {unsigned short tv_sec; unsigned short tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  RAND_seed (unsigned char*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned char* calloc (int,int) ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int get_random_bytes (unsigned char*,int) ; 
 unsigned short getpid () ; 
 int /*<<< orphan*/  kprintf (char*,char const*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,...) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 long long rdtsc () ; 
 int read (int,unsigned char*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

__attribute__((used)) static void prng_seed (const char *password_filename, int password_length) {
  unsigned char *a = calloc (64 + password_length, 1);
  assert (a != NULL);
  long long r = rdtsc ();
  struct timespec T;
  assert (clock_gettime(CLOCK_REALTIME, &T) >= 0);
  memcpy (a, &T.tv_sec, 4);
  memcpy (a+4, &T.tv_nsec, 4);
  memcpy (a+8, &r, 8);
  unsigned short p = getpid ();
  memcpy (a + 16, &p, 2);
  int s = get_random_bytes (a + 18, 32) + 18;
  int fd = open (password_filename, O_RDONLY);
  if (fd < 0) {
    kprintf ("Warning: fail to open password file - \"%s\", %m.\n", password_filename);
  } else {
    int l = read (fd, a + s, password_length);
    if (l < 0) {
      kprintf ("Warning: fail to read password file - \"%s\", %m.\n", password_filename);
    } else {
      vkprintf (1, "read %d bytes from password file.\n", l);
      s += l;
    }
    close (fd);
  }
  RAND_seed (a, s);
  memset (a, 0, s);
  free (a);
}