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
 int RAND_bytes (unsigned char*,int) ; 
 int RAND_pseudo_bytes (unsigned char*,int) ; 
 int /*<<< orphan*/  RAND_seed (unsigned char*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int get_random_bytes (unsigned char*,int) ; 
 unsigned short getpid () ; 
 int /*<<< orphan*/  memcpy (unsigned char*,...) ; 
 long long rdtsc () ; 

__attribute__((used)) static int generate_aes_key (unsigned char key[32], unsigned char iv[32]) {
  unsigned char a[64];
  long long r = rdtsc ();
  struct timespec T;
  assert (clock_gettime(CLOCK_REALTIME, &T) >= 0);
  memcpy (a, &T.tv_sec, 4);
  memcpy (a+4, &T.tv_nsec, 4);
  memcpy (a+8, &r, 8);
  unsigned short p = getpid ();
  memcpy (a + 16, &p, 2);
  int s = get_random_bytes (a + 18, 32);
  RAND_seed (a, s + 18);
  assert (RAND_bytes (key, 32));
  assert (RAND_pseudo_bytes (iv, 32));
  /*
  memcpy (a + 18, "ejudge was hacked", 17);
  int m = 18 + 17;
  unsigned salt[2] = {0x44af03bf, 0x2b515cb7};
  int i = EVP_BytesToKey (EVP_aes_256_cbc(), EVP_sha1(), (unsigned char *) salt, a, m, 128, key, iv);
  assert (i == 32);
  */
  return 0;
}