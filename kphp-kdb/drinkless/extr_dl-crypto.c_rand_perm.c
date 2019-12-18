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
struct timespec {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int* dl_malloc (size_t) ; 
 int rand () ; 
 int /*<<< orphan*/  srand (unsigned int) ; 
 int /*<<< orphan*/  usleep (int) ; 

int *rand_perm (int n) {
  int *v = dl_malloc ((size_t)n * sizeof (int)), i;

  usleep (1);
  struct timespec tv;
  assert (clock_gettime (CLOCK_REALTIME, &tv) >= 0);
  srand ((unsigned int)tv.tv_nsec * 123456789u + (unsigned int)tv.tv_sec * 987654321u);

  for (i = 0; i < n; i++) {
    v[i] = rand() % (i + 1);
  }

  return v;
}