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
struct tl_compiler {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  tl_compiler_init (struct tl_compiler*) ; 
 char* tl_readfile (struct tl_compiler*,char const* const) ; 
 int tl_schema_read (struct tl_compiler*,char*) ; 

int tl_schema_read_from_file (struct tl_compiler *C, const char *const filename) {
  tl_compiler_init (C);
  char *a = tl_readfile (C, filename);
  if (a == NULL) {
    return -1;
  }
  int r = tl_schema_read (C, a);
  free (a);

  return r;
}