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
struct timespec {int tv_sec; int tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int lrand48 () ; 
 int /*<<< orphan*/  md5 (unsigned char*,int,unsigned char*) ; 
 scalar_t__ rand_buf ; 
 long long rdtsc () ; 

int aes_generate_nonce (char res[16]) {
  *(int *)(rand_buf + 16) = lrand48 ();
  *(int *)(rand_buf + 20) = lrand48 ();
  *(long long *)(rand_buf + 24) = rdtsc ();
  struct timespec T;
  assert (clock_gettime(CLOCK_REALTIME, &T) >= 0);
  *(int *)(rand_buf + 32) = T.tv_sec;
  *(int *)(rand_buf + 36) = T.tv_nsec;
  (*(int *)(rand_buf + 40))++;

  md5 ((unsigned char *)rand_buf, 44, (unsigned char *)res);
  return 0;
}