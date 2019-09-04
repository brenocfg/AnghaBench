#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  last_data_time; int /*<<< orphan*/  first_data_time; int /*<<< orphan*/  random_tag; int /*<<< orphan*/  hostname; int /*<<< orphan*/  volume_id; int /*<<< orphan*/  disabled; } ;
typedef  TYPE_1__ host_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  a ;

/* Variables and functions */
 TYPE_1__** HOSTS ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__** calloc (int,int) ; 
 int /*<<< orphan*/  cmp_phost_t ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 int hosts ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  qsort (TYPE_1__**,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 
 int /*<<< orphan*/  weak_cmp_phost_t (TYPE_1__*,TYPE_1__*) ; 

char *get_collisions_list (void) {
  vkprintf (3, "get_collistions_list: hosts = %d\n", hosts);
  int i, j, k;
  char buf[1024];
  if (!hosts) {
    return NULL;
  }
  host_t **a = calloc (hosts, sizeof (a[0]));
  if (a == NULL) {
    return NULL;
  }
  int n = 0;
  for (i = 0; i < hosts; i++) {
    if (!HOSTS[i+1]->disabled) {
      a[n++] = HOSTS[i+1];
    }
  }
  if (!n) {
    return NULL;
  }
  qsort (a, n, sizeof (a[0]), cmp_phost_t);
  int l = 0;
  for (i = 0; i < n; i = j) {
    for (j = i + 1; j < n && !weak_cmp_phost_t (a[i], a[j]); j++) { }
    int m = j - i;
    if (m > 1) {
      for (k = i; k < j; k++) {
        l += snprintf (buf, sizeof (buf), "%llu,%s,0x%llx,%d,%d\n", a[k]->volume_id, a[k]->hostname, a[k]->random_tag, a[k]->first_data_time, a[k]->last_data_time);
      }
    }
  }
  if (l == 0) {
    return strdup ("");
  }
  l++;
  char *z = malloc (l), *p = z;
  if (z == NULL) {
    free (a);
    return NULL;
  }
  for (i = 0; i < n; i = j) {
    for (j = i + 1; j < n && !weak_cmp_phost_t (a[i], a[j]); j++) { }
    int m = j - i;
    if (m > 1) {
      for (k = i; k < j; k++) {
        p += sprintf (p, "%llu,%s,0x%llx,%d,%d\n", a[k]->volume_id, a[k]->hostname, a[k]->random_tag, a[k]->first_data_time, a[k]->last_data_time);
      }
    }
  }
  free (a);
  assert (p == (z + l - 1));
  return z;
}