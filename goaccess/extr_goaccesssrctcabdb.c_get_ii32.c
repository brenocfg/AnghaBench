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
 void* tcadbget (void*,int*,int,int*) ; 

__attribute__((used)) static int
get_ii32 (void *hash, int key)
{
  int sp, ret = 0;
  void *ptr = 0;

  if (!hash)
    return -1;

  /* key found, return current value */
  if ((ptr = tcadbget (hash, &key, sizeof (int), &sp)) != NULL) {
    ret = (*(int *) ptr);
    free (ptr);
    return ret;
  }

  return 0;
}