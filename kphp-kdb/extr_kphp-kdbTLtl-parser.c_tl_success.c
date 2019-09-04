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
struct tl_compiler {int errors; scalar_t__* error_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  cstr_free (scalar_t__*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,struct tl_compiler*,int) ; 

int tl_success (struct tl_compiler *C, int old_errors) {
  vkprintf (5, "tl_success (%p, %d)\n", C, old_errors);
  while (C->errors > old_errors) {
    C->errors--;
    if (C->error_msg[C->errors]) {
      cstr_free (&C->error_msg[C->errors]);
    }
  }
  return 0;
}