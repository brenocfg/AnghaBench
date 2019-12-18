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
struct bundle {int dummy; } ;

/* Variables and functions */
 int MAXARGS ; 
 int command_Expand_Interpret (char*,int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  command_Run (struct bundle*,int,char const* const*,struct prompt*,char const*,int /*<<< orphan*/ *) ; 

int
command_Decode(struct bundle *bundle, char *buff, int nb, struct prompt *prompt,
              const char *label)
{
  int argc;
  char *argv[MAXARGS];

  if ((argc = command_Expand_Interpret(buff, nb, argv, 0)) < 0)
    return 0;

  command_Run(bundle, argc, (char const *const *)argv, prompt, label, NULL);
  return 1;
}