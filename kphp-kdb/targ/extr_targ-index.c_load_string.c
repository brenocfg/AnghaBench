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
 char* exact_strdup (char*,int) ; 
 char* idx_rptr ; 
 int preload_string () ; 

char *load_string (void) {
  int len = preload_string ();
  if (!len) {
    ++idx_rptr;
    return 0;
  }
  char *str = idx_rptr;
  idx_rptr += len + 1;
  //  fprintf (stderr, "loaded string %s at %p\n", str, str);
  return exact_strdup (str, len);
}