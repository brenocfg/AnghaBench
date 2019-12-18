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
struct cmdargs {int argc; int argn; int /*<<< orphan*/ * argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  LibAliasSetSkinnyPort (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  la ; 
 long strtol (int /*<<< orphan*/ ,char**,int) ; 

int
nat_SkinnyPort(struct cmdargs const *arg)
{
  char *end;
  long port;

  if (arg->argc == arg->argn) {
    LibAliasSetSkinnyPort(la, 0);
    return 0;
  }

  if (arg->argc != arg->argn + 1)
    return -1;

  port = strtol(arg->argv[arg->argn], &end, 10);
  if (*end != '\0' || port < 0)
    return -1;

  LibAliasSetSkinnyPort(la, port);

  return 0;
}