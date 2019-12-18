#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  arc_flags_t ;
struct TYPE_5__ {int /*<<< orphan*/  b_flags; } ;
typedef  TYPE_1__ arc_buf_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ HDR_EMPTY (TYPE_1__*) ; 
 int /*<<< orphan*/  HDR_LOCK (TYPE_1__*) ; 
 scalar_t__ MUTEX_HELD (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
arc_hdr_set_flags(arc_buf_hdr_t *hdr, arc_flags_t flags)
{
	ASSERT(MUTEX_HELD(HDR_LOCK(hdr)) || HDR_EMPTY(hdr));
	hdr->b_flags |= flags;
}