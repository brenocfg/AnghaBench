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
struct physical {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  Write; int /*<<< orphan*/  Read; int /*<<< orphan*/  IsSet; int /*<<< orphan*/  UpdateSet; int /*<<< orphan*/  type; } ;
struct chat {char* script; int arg; int /*<<< orphan*/  timeout; int /*<<< orphan*/  pause; int /*<<< orphan*/  buf; int /*<<< orphan*/  bufend; int /*<<< orphan*/  bufstart; int /*<<< orphan*/ * nargptr; int /*<<< orphan*/ * argptr; scalar_t__ argc; struct physical* physical; TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAT_DESCRIPTOR ; 
 int /*<<< orphan*/  chat_IsSet ; 
 int /*<<< orphan*/  chat_Read ; 
 int /*<<< orphan*/  chat_UpdateSet ; 
 int /*<<< orphan*/  chat_Write ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 

void
chat_Init(struct chat *c, struct physical *p)
{
  c->desc.type = CHAT_DESCRIPTOR;
  c->desc.UpdateSet = chat_UpdateSet;
  c->desc.IsSet = chat_IsSet;
  c->desc.Read = chat_Read;
  c->desc.Write = chat_Write;
  c->physical = p;
  *c->script = '\0';
  c->argc = 0;
  c->arg = -1;
  c->argptr = NULL;
  c->nargptr = NULL;
  c->bufstart = c->bufend = c->buf;

  memset(&c->pause, '\0', sizeof c->pause);
  memset(&c->timeout, '\0', sizeof c->timeout);
}