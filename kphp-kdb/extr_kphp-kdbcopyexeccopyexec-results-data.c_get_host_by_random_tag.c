#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned long long random_tag; int host_id; } ;
typedef  TYPE_1__ host_t ;

/* Variables and functions */
 TYPE_1__** HOSTS ; 
 int MAX_HOSTS ; 
 unsigned int MAX_HOSTS_PRIME ; 
 TYPE_1__** RT_HOSTS ; 
 int /*<<< orphan*/  exit (int) ; 
 int hosts ; 
 int /*<<< orphan*/  kprintf (char*,char*) ; 
 TYPE_1__* zmalloc0 (int) ; 

host_t *get_host_by_random_tag (unsigned long long random_tag, int force) {
  unsigned h1 = ((unsigned) random_tag) % MAX_HOSTS_PRIME;
  const unsigned h2 = 1 + (((unsigned) (random_tag >> 32)) % (MAX_HOSTS_PRIME - 1));
  while (RT_HOSTS[h1] != NULL) {
    if (RT_HOSTS[h1]->random_tag == random_tag) {
      return RT_HOSTS[h1];
    }
    if ((h1 += h2) >= MAX_HOSTS_PRIME) {
      h1 -= MAX_HOSTS_PRIME;
    }
  }

  if (force > 0) {
    if (hosts >= MAX_HOSTS - 2) {
      kprintf ("Too many hosts, MAX_HOST_PRIME in %s should be increased.\n", __FILE__);
      exit (1);
    }
    host_t *H = zmalloc0 (sizeof (*H));
    H->random_tag = random_tag;
    H->host_id = ++hosts;
    HOSTS[hosts] = H;
    RT_HOSTS[h1] = H;
    return H;
  }

  return NULL;
}