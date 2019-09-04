#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* hnext; int /*<<< orphan*/  alias; } ;
typedef  TYPE_1__ tftp_file_t ;

/* Variables and functions */
 TYPE_1__** HF ; 
 unsigned int TFTP_FILE_HASH_PRIME ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  tot_files ; 
 int /*<<< orphan*/  zstrdup (char const*) ; 
 TYPE_1__* ztmalloc0 (int const) ; 

tftp_file_t *get_file_f (const char *alias, int force) {
  unsigned int h = 0;
  const char *s;
  for (s = alias; *s; s++) {
    h = 239 * h + *s;
  }
  h %= TFTP_FILE_HASH_PRIME;
  assert (h >= 0 && h < TFTP_FILE_HASH_PRIME);
  tftp_file_t **p = HF + h, *V;
  while (*p) {
    V = *p;
    if (!strcmp (V->alias, alias)) {
      *p = V->hnext;
      if (force >= 0) {
        V->hnext = HF[h];
        HF[h] = V;
      }
      return V;
    }
    p = &V->hnext;
  }
  if (force > 0) {
    tot_files++;
    const int sz = sizeof (tftp_file_t);
    V = ztmalloc0 (sz);
    V->alias = zstrdup (alias);
    V->hnext = HF[h];
    return HF[h] = V;
  }
  return NULL;
}