#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct cmdargs {int argc; int argn; char** argv; TYPE_4__* cx; } ;
struct TYPE_8__ {TYPE_3__* physical; } ;
struct TYPE_5__ {int* EscMap; } ;
struct TYPE_6__ {TYPE_1__ cfg; } ;
struct TYPE_7__ {TYPE_2__ async; } ;

/* Variables and functions */
 int /*<<< orphan*/  sscanf (int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static int
SetEscape(struct cmdargs const *arg)
{
  int code;
  int argc = arg->argc - arg->argn;
  char const *const *argv = arg->argv + arg->argn;

  for (code = 0; code < 33; code++)
    arg->cx->physical->async.cfg.EscMap[code] = 0;

  while (argc-- > 0) {
    sscanf(*argv++, "%x", &code);
    code &= 0xff;
    arg->cx->physical->async.cfg.EscMap[code >> 3] |= (1 << (code & 7));
    arg->cx->physical->async.cfg.EscMap[32] = 1;
  }
  return 0;
}