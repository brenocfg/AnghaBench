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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 char* ttyname (int /*<<< orphan*/ ) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static int
open_term (char **buf)
{
  const char *term = "/dev/tty";

  if (!isatty (STDERR_FILENO) || (term = ttyname (STDERR_FILENO)) == 0) {
    if (!isatty (STDOUT_FILENO) || (term = ttyname (STDOUT_FILENO)) == 0) {
      if (!isatty (STDIN_FILENO) || (term = ttyname (STDIN_FILENO)) == 0) {
        term = "/dev/tty";
      }
    }
  }
  *buf = xstrdup (term);

  return open (term, O_RDONLY);
}