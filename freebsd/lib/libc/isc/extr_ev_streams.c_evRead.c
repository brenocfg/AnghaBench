#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct iovec {int dummy; } ;
struct TYPE_12__ {TYPE_2__* opaque; } ;
typedef  TYPE_1__ evStreamID ;
typedef  int /*<<< orphan*/  evStreamFunc ;
struct TYPE_13__ {int fd; struct TYPE_13__* next; struct TYPE_13__* prev; int /*<<< orphan*/ * nextDone; int /*<<< orphan*/ * prevDone; int /*<<< orphan*/  file; scalar_t__ flags; void* uap; int /*<<< orphan*/  func; } ;
typedef  TYPE_2__ evStream ;
struct TYPE_14__ {TYPE_2__* streams; } ;
typedef  TYPE_3__ evContext_p ;
struct TYPE_15__ {TYPE_3__* opaque; } ;
typedef  TYPE_4__ evContext ;

/* Variables and functions */
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  FREE (TYPE_2__*) ; 
 int /*<<< orphan*/  OKNEW (TYPE_2__*) ; 
 scalar_t__ copyvec (TYPE_2__*,struct iovec const*,int) ; 
 int errno ; 
 scalar_t__ evSelectFD (TYPE_4__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readable ; 

int
evRead(evContext opaqueCtx, int fd, const struct iovec *iov, int iocnt,
       evStreamFunc func, void *uap, evStreamID *id)
{
	evContext_p *ctx = opaqueCtx.opaque;
	evStream *new;
	int save;

	OKNEW(new);
	new->func = func;
	new->uap = uap;
	new->fd = fd;
	new->flags = 0;
	if (evSelectFD(opaqueCtx, fd, EV_READ, readable, new, &new->file) < 0)
		goto free;
	if (copyvec(new, iov, iocnt) < 0)
		goto free;
	new->prevDone = NULL;
	new->nextDone = NULL;
	if (ctx->streams != NULL)
		ctx->streams->prev = new;
	new->prev = NULL;
	new->next = ctx->streams;
	ctx->streams = new;
	if (id)
		id->opaque = new;
	return (0);
 free:
	save = errno;
	FREE(new);
	errno = save;
	return (-1);
}