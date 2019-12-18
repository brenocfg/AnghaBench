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
 int /*<<< orphan*/  free (void*) ; 
 void* tcadbget (void*,void*,int,int*) ; 
 int /*<<< orphan*/  tcadbiterinit (void*) ; 
 void* tcadbiternext (void*,int*) ; 

__attribute__((used)) static void
get_ii32_min_max (void *hash, int *min, int *max)
{
  int curvalue = 0, i = 0, ksize = 0, sp = 0;
  void *key, *ptr;

  tcadbiterinit (hash);
  while ((key = tcadbiternext (hash, &ksize)) != NULL) {
    if ((ptr = tcadbget (hash, key, ksize, &sp)) == NULL) {
      free (key);
      continue;
    }

    curvalue = (*(int *) ptr);
    if (i++ == 0)
      *min = curvalue;
    if (curvalue > *max)
      *max = curvalue;
    if (curvalue < *min)
      *min = curvalue;
    free (key);
    free (ptr);
  }
}