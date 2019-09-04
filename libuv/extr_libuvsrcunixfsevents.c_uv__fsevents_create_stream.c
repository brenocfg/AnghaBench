#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* cf_state; } ;
typedef  TYPE_1__ uv_loop_t ;
struct TYPE_7__ {int /*<<< orphan*/ * fsevent_stream; int /*<<< orphan*/  loop; } ;
typedef  TYPE_2__ uv__cf_loop_state_t ;
struct TYPE_8__ {int /*<<< orphan*/ * copyDescription; int /*<<< orphan*/ * release; int /*<<< orphan*/ * retain; TYPE_1__* info; scalar_t__ version; } ;
typedef  int /*<<< orphan*/ * FSEventStreamRef ;
typedef  int FSEventStreamCreateFlags ;
typedef  TYPE_3__ FSEventStreamContext ;
typedef  int /*<<< orphan*/  CFArrayRef ;
typedef  double CFAbsoluteTime ;

/* Variables and functions */
 int UV_EMFILE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int kFSEventStreamCreateFlagFileEvents ; 
 int kFSEventStreamCreateFlagNoDefer ; 
 int /*<<< orphan*/  kFSEventStreamEventIdSinceNow ; 
 int /*<<< orphan*/ * pFSEventStreamCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,int) ; 
 int /*<<< orphan*/  pFSEventStreamInvalidate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pFSEventStreamRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pFSEventStreamScheduleWithRunLoop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pFSEventStreamStart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pkCFRunLoopDefaultMode ; 
 int /*<<< orphan*/  uv__fsevents_event_cb ; 

__attribute__((used)) static int uv__fsevents_create_stream(uv_loop_t* loop, CFArrayRef paths) {
  uv__cf_loop_state_t* state;
  FSEventStreamContext ctx;
  FSEventStreamRef ref;
  CFAbsoluteTime latency;
  FSEventStreamCreateFlags flags;

  /* Initialize context */
  ctx.version = 0;
  ctx.info = loop;
  ctx.retain = NULL;
  ctx.release = NULL;
  ctx.copyDescription = NULL;

  latency = 0.05;

  /* Explanation of selected flags:
   * 1. NoDefer - without this flag, events that are happening continuously
   *    (i.e. each event is happening after time interval less than `latency`,
   *    counted from previous event), will be deferred and passed to callback
   *    once they'll either fill whole OS buffer, or when this continuous stream
   *    will stop (i.e. there'll be delay between events, bigger than
   *    `latency`).
   *    Specifying this flag will invoke callback after `latency` time passed
   *    since event.
   * 2. FileEvents - fire callback for file changes too (by default it is firing
   *    it only for directory changes).
   */
  flags = kFSEventStreamCreateFlagNoDefer | kFSEventStreamCreateFlagFileEvents;

  /*
   * NOTE: It might sound like a good idea to remember last seen StreamEventId,
   * but in reality one dir might have last StreamEventId less than, the other,
   * that is being watched now. Which will cause FSEventStream API to report
   * changes to files from the past.
   */
  ref = pFSEventStreamCreate(NULL,
                             &uv__fsevents_event_cb,
                             &ctx,
                             paths,
                             kFSEventStreamEventIdSinceNow,
                             latency,
                             flags);
  assert(ref != NULL);

  state = loop->cf_state;
  pFSEventStreamScheduleWithRunLoop(ref,
                                    state->loop,
                                    *pkCFRunLoopDefaultMode);
  if (!pFSEventStreamStart(ref)) {
    pFSEventStreamInvalidate(ref);
    pFSEventStreamRelease(ref);
    return UV_EMFILE;
  }

  state->fsevent_stream = ref;
  return 0;
}