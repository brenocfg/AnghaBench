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
struct nat64lsn_pg {int chunks_count; struct nat64lsn_pg** freemask_chunk; struct nat64lsn_pg** states_chunk; struct nat64lsn_pg* states; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NAT64LSN ; 
 int /*<<< orphan*/  free (struct nat64lsn_pg**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nat64lsn_pg_zone ; 
 int /*<<< orphan*/  nat64lsn_state_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct nat64lsn_pg*) ; 

__attribute__((used)) static void
nat64lsn_destroy_pg(struct nat64lsn_pg *pg)
{
	int i;

	if (pg->chunks_count == 1) {
		uma_zfree(nat64lsn_state_zone, pg->states);
	} else {
		for (i = 0; i < pg->chunks_count; i++)
			uma_zfree(nat64lsn_state_zone, pg->states_chunk[i]);
		free(pg->states_chunk, M_NAT64LSN);
		free(pg->freemask_chunk, M_NAT64LSN);
	}
	uma_zfree(nat64lsn_pg_zone, pg);
}