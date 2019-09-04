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
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* realpath (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (scalar_t__) ; 

int main(int argc, char* argv[]) {
  int num_errors = 0;
  errno = 0;

  for (int i = 1; i < argc; ++i) {
    char* p = realpath(argv[i], NULL);
    if (p == NULL) {
      fprintf(stderr, "Error resolving path '%s', error was: '%s'\n",
              argv[i], strerror(errno));
      errno = 0;
      ++num_errors;
    } else {
      fprintf(stdout, "%s\n", p);
      free(p);
    }
  }

  return num_errors == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}