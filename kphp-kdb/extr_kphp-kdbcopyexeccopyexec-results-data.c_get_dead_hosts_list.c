#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  a ;
struct TYPE_2__ {unsigned long long volume_id; int last_action_time; char* hostname; int /*<<< orphan*/  disabled; } ;

/* Variables and functions */
 TYPE_1__** HOSTS ; 
 int /*<<< orphan*/  assert (int) ; 
 int* calloc (int,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 int hosts ; 
 char* malloc (int) ; 
 int now ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,unsigned long long,int) ; 

char *get_dead_hosts_list (unsigned long long volume_id, int delay) {
  vkprintf (3, "get_dead_hosts_list (volume_id:%llu, delay: %d)\n", volume_id, delay);
  int *a = calloc (hosts, sizeof (a[0]));
  if (a == NULL) {
    return NULL;
  }
  int i, n = 0, l = 0, t = now - delay;
  for (i = 1; i <= hosts; i++) {
    if (HOSTS[i]->volume_id == volume_id && !HOSTS[i]->disabled && HOSTS[i]->last_action_time < t) {
      a[n++] = i;
      l += strlen (HOSTS[i]->hostname) + 1;
    }
  }
  if (!n) {
    return strdup ("");
  }
  char *z = malloc (l), *p = z;
  if (z == NULL) {
    free (a);
    return NULL;
  }

  for (i = 0; i < n; i++) {
    if (i > 0) {
      *p++= ',';
    }
    strcpy (p, HOSTS[a[i]]->hostname);
    p += strlen (p);
  }
  assert (p == (z + l - 1));
  free (a);
  return z;
}