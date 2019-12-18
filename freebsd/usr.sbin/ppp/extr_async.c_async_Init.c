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
struct TYPE_2__ {int /*<<< orphan*/  EscMap; } ;
struct async {TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  async_Setup (struct async*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,int) ; 

void
async_Init(struct async *async)
{
  async_Setup(async);
  memset(async->cfg.EscMap, '\0', sizeof async->cfg.EscMap);
}