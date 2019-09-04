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
 int /*<<< orphan*/  exit (int) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long) ; 

void *xmalloc(size_t size) {
  void *ptr;

  ptr = malloc(size);
  if (ptr == NULL) {
    pr_err("out of memory, need %lu bytes", (unsigned long) size);
    exit(1);
  }

  return ptr;
}