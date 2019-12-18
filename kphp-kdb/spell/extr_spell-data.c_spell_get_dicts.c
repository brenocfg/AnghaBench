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
struct TYPE_2__ {char* code; char* jargon; int /*<<< orphan*/ ** stat; } ;

/* Variables and functions */
 TYPE_1__** SC ; 
 int snprintf (char*,int,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spellers ; 

int spell_get_dicts (char *buf, int len) {
  int i;
  char *p = buf;
  char *e = buf + len - 2;
  for (i = 0; i < spellers; i++) {
    int o = e - p;
    if (o < 5) {
      break ;
    }
    int l = snprintf (p, o, "%s\t%s\t%lld\t%lld\t%lld\t%lld\n", SC[i]->code, SC[i]->jargon, SC[i]->stat[0][0], SC[i]->stat[0][1], SC[i]->stat[1][0], SC[i]->stat[1][1]);
    if (l < 0 || l >= o) {
      *p = 0;
      break;
    }
    p += l;
  }
  return p - buf;
}