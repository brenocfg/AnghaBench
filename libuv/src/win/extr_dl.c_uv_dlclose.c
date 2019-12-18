#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * handle; int /*<<< orphan*/ * errmsg; } ;
typedef  TYPE_1__ uv_lib_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LocalFree (void*) ; 

void uv_dlclose(uv_lib_t* lib) {
  if (lib->errmsg) {
    LocalFree((void*)lib->errmsg);
    lib->errmsg = NULL;
  }

  if (lib->handle) {
    /* Ignore errors. No good way to signal them without leaking memory. */
    FreeLibrary(lib->handle);
    lib->handle = NULL;
  }
}