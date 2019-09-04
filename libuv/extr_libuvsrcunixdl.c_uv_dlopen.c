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
struct TYPE_4__ {scalar_t__ handle; int /*<<< orphan*/ * errmsg; } ;
typedef  TYPE_1__ uv_lib_t ;

/* Variables and functions */
 int /*<<< orphan*/  RTLD_LAZY ; 
 int /*<<< orphan*/  dlerror () ; 
 scalar_t__ dlopen (char const*,int /*<<< orphan*/ ) ; 
 int uv__dlerror (TYPE_1__*) ; 

int uv_dlopen(const char* filename, uv_lib_t* lib) {
  dlerror(); /* Reset error status. */
  lib->errmsg = NULL;
  lib->handle = dlopen(filename, RTLD_LAZY);
  return lib->handle ? 0 : uv__dlerror(lib);
}