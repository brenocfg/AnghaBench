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
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 char* tmp_mem_alloc (int) ; 

char *tmp_mem_strdup (char *s) {
  int n = strlen (s) + 1;
  char *v = tmp_mem_alloc (n);
  memcpy (v, s, n);
  return v;
}