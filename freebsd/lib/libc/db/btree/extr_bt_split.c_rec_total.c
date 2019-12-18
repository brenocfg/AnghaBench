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
typedef  scalar_t__ recno_t ;
typedef  scalar_t__ indx_t ;
struct TYPE_2__ {scalar_t__ nrecs; } ;
typedef  int /*<<< orphan*/  PAGE ;

/* Variables and functions */
 TYPE_1__* GETRINTERNAL (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ NEXTINDEX (int /*<<< orphan*/ *) ; 

__attribute__((used)) static recno_t
rec_total(PAGE *h)
{
	recno_t recs;
	indx_t nxt, top;

	for (recs = 0, nxt = 0, top = NEXTINDEX(h); nxt < top; ++nxt)
		recs += GETRINTERNAL(h, nxt)->nrecs;
	return (recs);
}