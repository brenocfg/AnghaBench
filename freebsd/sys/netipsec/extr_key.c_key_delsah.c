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
struct secashead {scalar_t__ state; int /*<<< orphan*/  savtree_alive; int /*<<< orphan*/  savtree_larval; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSEC_ASSERT (int,char*) ; 
 int /*<<< orphan*/  M_IPSEC_SAH ; 
 scalar_t__ SADB_SASTATE_DEAD ; 
 int TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct secashead*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
key_delsah(struct secashead *sah)
{
	IPSEC_ASSERT(sah != NULL, ("NULL sah"));
	IPSEC_ASSERT(sah->state == SADB_SASTATE_DEAD,
	    ("Attempt to free non DEAD SAH %p", sah));
	IPSEC_ASSERT(TAILQ_EMPTY(&sah->savtree_larval),
	    ("Attempt to free SAH %p with LARVAL SA", sah));
	IPSEC_ASSERT(TAILQ_EMPTY(&sah->savtree_alive),
	    ("Attempt to free SAH %p with ALIVE SA", sah));

	free(sah, M_IPSEC_SAH);
}