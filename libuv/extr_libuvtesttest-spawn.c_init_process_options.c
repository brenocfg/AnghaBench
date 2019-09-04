#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_exit_cb ;
struct TYPE_2__ {char* file; char** args; scalar_t__ flags; int /*<<< orphan*/  exit_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 char** args ; 
 char* exepath ; 
 size_t exepath_size ; 
 TYPE_1__ options ; 
 int uv_exepath (char*,size_t*) ; 

__attribute__((used)) static void init_process_options(char* test, uv_exit_cb exit_cb) {
  /* Note spawn_helper1 defined in test/run-tests.c */
  int r = uv_exepath(exepath, &exepath_size);
  ASSERT(r == 0);
  exepath[exepath_size] = '\0';
  args[0] = exepath;
  args[1] = test;
  args[2] = NULL;
  args[3] = NULL;
  args[4] = NULL;
  options.file = exepath;
  options.args = args;
  options.exit_cb = exit_cb;
  options.flags = 0;
}