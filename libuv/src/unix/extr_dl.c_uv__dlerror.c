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
struct TYPE_3__ {int /*<<< orphan*/ * errmsg; } ;
typedef  TYPE_1__ uv_lib_t ;

/* Variables and functions */
 char* dlerror () ; 
 int /*<<< orphan*/  uv__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uv__strdup (char const*) ; 

__attribute__((used)) static int uv__dlerror(uv_lib_t* lib) {
  const char* errmsg;

  uv__free(lib->errmsg);

  errmsg = dlerror();

  if (errmsg) {
    lib->errmsg = uv__strdup(errmsg);
    return -1;
  }
  else {
    lib->errmsg = NULL;
    return 0;
  }
}