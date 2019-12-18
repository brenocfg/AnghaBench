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
struct TYPE_3__ {int /*<<< orphan*/ * dl; } ;
struct TYPE_4__ {int /*<<< orphan*/  Write; int /*<<< orphan*/  Read; int /*<<< orphan*/  IsSet; int /*<<< orphan*/  UpdateSet; int /*<<< orphan*/  type; } ;
struct mpserver {int fd; int /*<<< orphan*/  socket; TYPE_1__ send; TYPE_2__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPSERVER_DESCRIPTOR ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  mpserver_IsSet ; 
 int /*<<< orphan*/  mpserver_Read ; 
 int /*<<< orphan*/  mpserver_UpdateSet ; 
 int /*<<< orphan*/  mpserver_Write ; 

void
mpserver_Init(struct mpserver *s)
{
  s->desc.type = MPSERVER_DESCRIPTOR;
  s->desc.UpdateSet = mpserver_UpdateSet;
  s->desc.IsSet = mpserver_IsSet;
  s->desc.Read = mpserver_Read;
  s->desc.Write = mpserver_Write;
  s->send.dl = NULL;
  s->fd = -1;
  memset(&s->socket, '\0', sizeof s->socket);
}