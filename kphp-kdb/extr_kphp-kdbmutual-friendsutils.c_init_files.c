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
 int /*<<< orphan*/  assert (int) ; 
 int f_inited ; 
 void* fcurr ; 
 void* fd ; 
 void* fnames ; 
 void* fsize ; 
 void* qmalloc0 (int) ; 

void init_files (int fn) {
  assert (!f_inited);
  fnames = qmalloc0 (sizeof (char *) * fn);
  fd = qmalloc0 (sizeof (int) * fn);
  fsize = qmalloc0 (sizeof (long long) * fn);
  fcurr = qmalloc0 (sizeof (long long) * fn);
  f_inited = fn;
}