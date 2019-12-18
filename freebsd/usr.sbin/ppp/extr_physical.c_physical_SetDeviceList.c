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
struct TYPE_2__ {char* devlist; int ndev; } ;
struct physical {TYPE_1__ cfg; } ;

/* Variables and functions */
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const* const,int) ; 

void
physical_SetDeviceList(struct physical *p, int argc, const char *const *argv)
{
  unsigned pos;
  int f;

  p->cfg.devlist[sizeof p->cfg.devlist - 1] = '\0';
  for (f = 0, pos = 0; f < argc && pos < sizeof p->cfg.devlist - 1; f++) {
    if (pos)
      p->cfg.devlist[pos++] = '\0';
    strncpy(p->cfg.devlist + pos, argv[f], sizeof p->cfg.devlist - pos - 1);
    pos += strlen(p->cfg.devlist + pos);
  }
  p->cfg.ndev = f;
}