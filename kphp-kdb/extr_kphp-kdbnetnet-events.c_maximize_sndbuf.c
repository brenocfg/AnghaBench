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
typedef  int socklen_t ;

/* Variables and functions */
 int MAX_UDP_SENDBUF_SIZE ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,int,int) ; 

void maximize_sndbuf (int sfd, int max) {
  socklen_t intsize = sizeof(int);
  int last_good = 0;
  int min, avg;
  int old_size;

  if (max <= 0) {
    max = MAX_UDP_SENDBUF_SIZE;
  }

  /* Start with the default size. */
  if (getsockopt (sfd, SOL_SOCKET, SO_SNDBUF, &old_size, &intsize)) {
    if (verbosity > 0) {
      perror ("getsockopt (SO_SNDBUF)");
    }
    return;
  }

  /* Binary-search for the real maximum. */
  min = last_good = old_size;
  max = MAX_UDP_SENDBUF_SIZE;

  while (min <= max) {
    avg = ((unsigned int) min + max) / 2;
    if (setsockopt (sfd, SOL_SOCKET, SO_SNDBUF, &avg, intsize) == 0) {
      last_good = avg;
      min = avg + 1;
    } else {
      max = avg - 1;
    }
  }

  vkprintf (2, "<%d send buffer was %d, now %d\n", sfd, old_size, last_good);
}