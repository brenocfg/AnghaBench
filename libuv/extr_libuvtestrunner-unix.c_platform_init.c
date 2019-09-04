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
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  _IONBF ; 
 int /*<<< orphan*/  executable_path ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/ * realpath (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

int platform_init(int argc, char **argv) {
  /* Disable stdio output buffering. */
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  signal(SIGPIPE, SIG_IGN);

  if (realpath(argv[0], executable_path) == NULL) {
    perror("realpath");
    return -1;
  }

  return 0;
}