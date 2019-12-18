#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct iovec {int dummy; } ;
struct TYPE_16__ {TYPE_5__* opaque; } ;
typedef  TYPE_4__ evStreamID ;
struct TYPE_20__ {scalar_t__ opaque; } ;
struct TYPE_17__ {int iovOrigCount; int /*<<< orphan*/  iovOrig; TYPE_9__ file; TYPE_3__* prevDone; struct TYPE_17__* nextDone; TYPE_2__* prev; TYPE_1__* next; } ;
typedef  TYPE_5__ evStream ;
struct TYPE_18__ {TYPE_3__* strLast; TYPE_5__* strDone; TYPE_1__* streams; } ;
typedef  TYPE_6__ evContext_p ;
struct TYPE_19__ {TYPE_6__* opaque; } ;
typedef  TYPE_7__ evContext ;
struct TYPE_15__ {TYPE_5__* nextDone; } ;
struct TYPE_14__ {TYPE_1__* next; } ;
struct TYPE_13__ {TYPE_2__* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (TYPE_5__*) ; 
 int /*<<< orphan*/  evDeselectFD (TYPE_7__,TYPE_9__) ; 
 int /*<<< orphan*/  memput (int /*<<< orphan*/ ,int) ; 

int
evCancelRW(evContext opaqueCtx, evStreamID id) {
	evContext_p *ctx = opaqueCtx.opaque;
	evStream *old = id.opaque;

	/*
	 * The streams list is doubly threaded.  First, there's ctx->streams
	 * that's used by evDestroy() to find and cancel all streams.  Second,
	 * there's ctx->strDone (head) and ctx->strLast (tail) which thread
	 * through the potentially smaller number of "IO completed" streams,
	 * used in evGetNext() to avoid scanning the entire list.
	 */

	/* Unlink from ctx->streams. */
	if (old->prev != NULL)
		old->prev->next = old->next;
	else
		ctx->streams = old->next;
	if (old->next != NULL)
		old->next->prev = old->prev;

	/*
	 * If 'old' is on the ctx->strDone list, remove it.  Update
	 * ctx->strLast if necessary.
	 */
	if (old->prevDone == NULL && old->nextDone == NULL) {
		/*
		 * Either 'old' is the only item on the done list, or it's
		 * not on the done list.  If the former, then we unlink it
		 * from the list.  If the latter, we leave the list alone.
		 */
		if (ctx->strDone == old) {
			ctx->strDone = NULL;
			ctx->strLast = NULL;
		}
	} else {
		if (old->prevDone != NULL)
			old->prevDone->nextDone = old->nextDone;
		else
			ctx->strDone = old->nextDone;
		if (old->nextDone != NULL)
			old->nextDone->prevDone = old->prevDone;
		else
			ctx->strLast = old->prevDone;
	}

	/* Deallocate the stream. */
	if (old->file.opaque)
		evDeselectFD(opaqueCtx, old->file);
	memput(old->iovOrig, sizeof (struct iovec) * old->iovOrigCount);
	FREE(old);
	return (0);
}