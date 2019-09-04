#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int maxclients; TYPE_1__* clientinfo; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; scalar_t__ infoValid; } ;

/* Variables and functions */
 scalar_t__ Q_stricmp (int /*<<< orphan*/ ,char const*) ; 
 TYPE_2__ cgs ; 

int CG_ClientNumFromName(const char *p) {
  int i;
  for (i = 0; i < cgs.maxclients; i++) {
    if (cgs.clientinfo[i].infoValid && Q_stricmp(cgs.clientinfo[i].name, p) == 0) {
      return i;
    }
  }
  return -1;
}