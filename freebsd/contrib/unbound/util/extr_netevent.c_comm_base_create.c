#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct internal_base {int /*<<< orphan*/  base; struct internal_base* eb; int /*<<< orphan*/  now; int /*<<< orphan*/  secs; } ;
struct comm_base {int /*<<< orphan*/  base; struct comm_base* eb; int /*<<< orphan*/  now; int /*<<< orphan*/  secs; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct internal_base*) ; 
 int /*<<< orphan*/  ub_comm_base_now (struct internal_base*) ; 
 int /*<<< orphan*/  ub_default_event_base (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ub_get_event_sys (int /*<<< orphan*/ ,char const**,char const**,char const**) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,char const*,char const*,char const*) ; 

struct comm_base* 
comm_base_create(int sigs)
{
	struct comm_base* b = (struct comm_base*)calloc(1,
		sizeof(struct comm_base));
	const char *evnm="event", *evsys="", *evmethod="";

	if(!b)
		return NULL;
	b->eb = (struct internal_base*)calloc(1, sizeof(struct internal_base));
	if(!b->eb) {
		free(b);
		return NULL;
	}
	b->eb->base = ub_default_event_base(sigs, &b->eb->secs, &b->eb->now);
	if(!b->eb->base) {
		free(b->eb);
		free(b);
		return NULL;
	}
	ub_comm_base_now(b);
	ub_get_event_sys(b->eb->base, &evnm, &evsys, &evmethod);
	verbose(VERB_ALGO, "%s %s uses %s method.", evnm, evsys, evmethod);
	return b;
}