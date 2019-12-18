#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mstate ;
typedef  TYPE_2__* msegmentptr ;
typedef  TYPE_3__* mchunkptr ;
struct TYPE_18__ {scalar_t__ head; } ;
struct TYPE_17__ {struct TYPE_17__* next; int /*<<< orphan*/  base; } ;
struct TYPE_16__ {size_t max_footprint; size_t footprint; size_t topsize; TYPE_3__* top; TYPE_2__ seg; } ;

/* Variables and functions */
 scalar_t__ FENCEPOST_HEAD ; 
 int /*<<< orphan*/  POSTACTION (TYPE_1__*) ; 
 int /*<<< orphan*/  PREACTION (TYPE_1__*) ; 
 size_t TOP_FOOT_SIZE ; 
 TYPE_3__* align_as_chunk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_malloc_state (TYPE_1__*) ; 
 scalar_t__ chunksize (TYPE_3__*) ; 
 int /*<<< orphan*/  cinuse (TYPE_3__*) ; 
 int /*<<< orphan*/  ensure_initialization () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned long) ; 
 scalar_t__ is_initialized (TYPE_1__*) ; 
 TYPE_3__* next_chunk (TYPE_3__*) ; 
 scalar_t__ segment_holds (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void internal_malloc_stats(mstate m) {
  ensure_initialization();
  if (!PREACTION(m)) {
    size_t maxfp = 0;
    size_t fp = 0;
    size_t used = 0;
    check_malloc_state(m);
    if (is_initialized(m)) {
      msegmentptr s = &m->seg;
      maxfp = m->max_footprint;
      fp = m->footprint;
      used = fp - (m->topsize + TOP_FOOT_SIZE);

      while (s != 0) {
	mchunkptr q = align_as_chunk(s->base);
	while (segment_holds(s, q) &&
	       q != m->top && q->head != FENCEPOST_HEAD) {
	  if (!cinuse(q))
	    used -= chunksize(q);
	  q = next_chunk(q);
	}
	s = s->next;
      }
    }

    fprintf(stderr, "max system bytes = %10lu\n", (unsigned long)(maxfp));
    fprintf(stderr, "system bytes     = %10lu\n", (unsigned long)(fp));
    fprintf(stderr, "in use bytes     = %10lu\n", (unsigned long)(used));

    POSTACTION(m);
  }
}