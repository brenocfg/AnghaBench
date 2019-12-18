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
struct TYPE_2__ {char* address; scalar_t__ len; scalar_t__ class; } ;
struct peerid {char* authname; TYPE_1__ enddisc; } ;

/* Variables and functions */

void
peerid_Init(struct peerid *peer)
{
  peer->enddisc.class = 0;
  *peer->enddisc.address = '\0';
  peer->enddisc.len = 0;
  *peer->authname = '\0';
}