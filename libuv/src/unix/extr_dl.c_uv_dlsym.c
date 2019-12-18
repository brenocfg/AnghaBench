#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ uv_lib_t ;

/* Variables and functions */
 int /*<<< orphan*/  dlerror () ; 
 void* dlsym (int /*<<< orphan*/ ,char const*) ; 
 int uv__dlerror (TYPE_1__*) ; 

int uv_dlsym(uv_lib_t* lib, const char* name, void** ptr) {
  dlerror(); /* Reset error status. */
  *ptr = dlsym(lib->handle, name);
  return uv__dlerror(lib);
}