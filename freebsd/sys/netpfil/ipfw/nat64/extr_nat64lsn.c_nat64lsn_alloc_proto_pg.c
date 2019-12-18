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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct nat64lsn_states_chunk {int dummy; } ;
struct nat64lsn_pgchunk {struct nat64lsn_pg** pgptr; } ;
struct nat64lsn_pg {int chunks_count; struct nat64lsn_pg** states_chunk; struct nat64lsn_pg** freemask_chunk; scalar_t__ base_port; int /*<<< orphan*/  proto; int /*<<< orphan*/  timestamp; struct nat64lsn_pg* freemask64; int /*<<< orphan*/ * states; } ;
struct TYPE_2__ {int /*<<< orphan*/  stats; } ;
struct nat64lsn_cfg {int states_chunks; TYPE_1__ base; } ;
struct nat64lsn_alias {int /*<<< orphan*/  portgroups_count; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  portgroups; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIAS_LOCK (struct nat64lsn_alias*) ; 
 int /*<<< orphan*/  ALIAS_UNLOCK (struct nat64lsn_alias*) ; 
 int /*<<< orphan*/  CK_SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct nat64lsn_pg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISSET32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  M_NAT64LSN ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NAT64STAT_INC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ NAT64_MIN_PORT ; 
 int PG_ERROR (int) ; 
 int /*<<< orphan*/  SET_AGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ck_pr_bts_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ck_pr_fence_store () ; 
 int /*<<< orphan*/  ck_pr_store_ptr (struct nat64lsn_pg**,struct nat64lsn_pg*) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  free (struct nat64lsn_pg**,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct nat64lsn_pg**,int,int) ; 
 int nat64lsn_find_pg_place (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nat64lsn_pg_zone ; 
 int /*<<< orphan*/  nat64lsn_pgchunk_zone ; 
 int /*<<< orphan*/  nat64lsn_state_zone ; 
 int /*<<< orphan*/  spgcreated ; 
 void* uma_zalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct nat64lsn_pg*) ; 

__attribute__((used)) static int
nat64lsn_alloc_proto_pg(struct nat64lsn_cfg *cfg,
    struct nat64lsn_alias *alias, uint32_t *chunkmask,
    uint32_t *pgmask, struct nat64lsn_pgchunk **chunks,
    struct nat64lsn_pg **pgptr, uint8_t proto)
{
	struct nat64lsn_pg *pg;
	int i, pg_idx, chunk_idx;

	/* Find place in pgchunk where PG can be added */
	pg_idx = nat64lsn_find_pg_place(pgmask);
	if (pg_idx < 0)	/* no more PGs */
		return (PG_ERROR(1));
	/* Check that we have allocated pgchunk for given PG index */
	chunk_idx = pg_idx / 32;
	if (!ISSET32(*chunkmask, chunk_idx)) {
		chunks[chunk_idx] = uma_zalloc(nat64lsn_pgchunk_zone,
		    M_NOWAIT);
		if (chunks[chunk_idx] == NULL)
			return (PG_ERROR(2));
		ck_pr_bts_32(chunkmask, chunk_idx);
		ck_pr_fence_store();
	}
	/* Allocate PG and states chunks */
	pg = uma_zalloc(nat64lsn_pg_zone, M_NOWAIT);
	if (pg == NULL)
		return (PG_ERROR(3));
	pg->chunks_count = cfg->states_chunks;
	if (pg->chunks_count > 1) {
		pg->freemask_chunk = malloc(pg->chunks_count *
		    sizeof(uint64_t), M_NAT64LSN, M_NOWAIT);
		if (pg->freemask_chunk == NULL) {
			uma_zfree(nat64lsn_pg_zone, pg);
			return (PG_ERROR(4));
		}
		pg->states_chunk = malloc(pg->chunks_count *
		    sizeof(struct nat64lsn_states_chunk *), M_NAT64LSN,
		    M_NOWAIT | M_ZERO);
		if (pg->states_chunk == NULL) {
			free(pg->freemask_chunk, M_NAT64LSN);
			uma_zfree(nat64lsn_pg_zone, pg);
			return (PG_ERROR(5));
		}
		for (i = 0; i < pg->chunks_count; i++) {
			pg->states_chunk[i] = uma_zalloc(
			    nat64lsn_state_zone, M_NOWAIT);
			if (pg->states_chunk[i] == NULL)
				goto states_failed;
		}
		memset(pg->freemask_chunk, 0xff,
		    sizeof(uint64_t) * pg->chunks_count);
	} else {
		pg->states = uma_zalloc(nat64lsn_state_zone, M_NOWAIT);
		if (pg->states == NULL) {
			uma_zfree(nat64lsn_pg_zone, pg);
			return (PG_ERROR(6));
		}
		memset(&pg->freemask64, 0xff, sizeof(uint64_t));
	}

	/* Initialize PG and hook it to pgchunk */
	SET_AGE(pg->timestamp);
	pg->proto = proto;
	pg->base_port = NAT64_MIN_PORT + 64 * pg_idx;
	ck_pr_store_ptr(&chunks[chunk_idx]->pgptr[pg_idx % 32], pg);
	ck_pr_fence_store();
	ck_pr_bts_32(&pgmask[pg_idx / 32], pg_idx % 32);
	ck_pr_store_ptr(pgptr, pg);

	ALIAS_LOCK(alias);
	CK_SLIST_INSERT_HEAD(&alias->portgroups, pg, entries);
	SET_AGE(alias->timestamp);
	alias->portgroups_count++;
	ALIAS_UNLOCK(alias);
	NAT64STAT_INC(&cfg->base.stats, spgcreated);
	return (PG_ERROR(0));

states_failed:
	for (i = 0; i < pg->chunks_count; i++)
		uma_zfree(nat64lsn_state_zone, pg->states_chunk[i]);
	free(pg->freemask_chunk, M_NAT64LSN);
	free(pg->states_chunk, M_NAT64LSN);
	uma_zfree(nat64lsn_pg_zone, pg);
	return (PG_ERROR(7));
}