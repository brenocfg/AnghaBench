#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * opaque; } ;
struct TYPE_8__ {TYPE_5__ file; struct TYPE_8__* nextDone; struct TYPE_8__* prevDone; } ;
typedef  TYPE_1__ evStream ;
struct TYPE_9__ {TYPE_1__* strLast; TYPE_1__* strDone; } ;
typedef  TYPE_2__ evContext_p ;
struct TYPE_10__ {TYPE_2__* opaque; } ;
typedef  TYPE_3__ evContext ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evDeselectFD (TYPE_3__,TYPE_5__) ; 

__attribute__((used)) static void
done(evContext opaqueCtx, evStream *str) {
	evContext_p *ctx = opaqueCtx.opaque;

	if (ctx->strLast != NULL) {
		str->prevDone = ctx->strLast;
		ctx->strLast->nextDone = str;
		ctx->strLast = str;
	} else {
		INSIST(ctx->strDone == NULL);
		ctx->strDone = ctx->strLast = str;
	}
	evDeselectFD(opaqueCtx, str->file);
	str->file.opaque = NULL;
	/* evDrop() will call evCancelRW() on us. */
}