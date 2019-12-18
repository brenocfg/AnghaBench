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
struct TYPE_2__ {struct pending* key; } ;
struct pending {unsigned int id; TYPE_1__ node; } ;
struct outside_network {int /*<<< orphan*/  rnd; int /*<<< orphan*/  pending; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_ID_SET (int /*<<< orphan*/ ,unsigned int) ; 
 int MAX_ID_RETRY ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  rbtree_insert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ ub_random (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
select_id(struct outside_network* outnet, struct pending* pend,
	sldns_buffer* packet)
{
	int id_tries = 0;
	pend->id = ((unsigned)ub_random(outnet->rnd)>>8) & 0xffff;
	LDNS_ID_SET(sldns_buffer_begin(packet), pend->id);

	/* insert in tree */
	pend->node.key = pend;
	while(!rbtree_insert(outnet->pending, &pend->node)) {
		/* change ID to avoid collision */
		pend->id = ((unsigned)ub_random(outnet->rnd)>>8) & 0xffff;
		LDNS_ID_SET(sldns_buffer_begin(packet), pend->id);
		id_tries++;
		if(id_tries == MAX_ID_RETRY) {
			pend->id=99999; /* non existant ID */
			log_err("failed to generate unique ID, drop msg");
			return 0;
		}
	}
	verbose(VERB_ALGO, "inserted new pending reply id=%4.4x", pend->id);
	return 1;
}