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
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  zzfree (void*,int) ; 
 void* zzmalloc (int) ; 

void *zzrealloc (void *p, int old_len, int new_len) {
  void *tmp = zzmalloc (new_len);
  if (!tmp) {
    return 0;
  }
  int t = old_len;
  if (old_len > new_len) {
    t = old_len;
  }
  memcpy (tmp, p, t);
  if (p) {
    zzfree (p, old_len);
  }
  return tmp;
}