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
struct prompt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogWARN ; 
 int PHYS_DIRECT ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  log_Close () ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 char* system_IsValid (char const*,struct prompt*,int) ; 

__attribute__((used)) static void
CheckLabel(const char *label, struct prompt *prompt, int mode)
{
  const char *err;

  if ((err = system_IsValid(label, prompt, mode)) != NULL) {
    fprintf(stderr, "%s: %s\n", label, err);
    if (mode == PHYS_DIRECT)
      log_Printf(LogWARN, "Label %s rejected -direct connection: %s\n",
                 label, err);
    log_Close();
    exit(1);
  }
}