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
 int /*<<< orphan*/  free (char*) ; 
 char jv_mem_uninitialised ; 
 char* malloc (int) ; 

__attribute__((constructor)) void jv_mem_uninit_setup(){
  // ignore warning that this reads uninitialized memory - that's the point!
#ifndef __clang_analyzer__
  char* p = malloc(1);
  jv_mem_uninitialised = *p;
  free(p);
#endif
}