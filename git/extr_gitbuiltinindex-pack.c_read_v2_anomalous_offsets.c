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
typedef  int uint32_t ;
struct packed_git {int const num_objects; scalar_t__ index_data; } ;
struct pack_idx_option {scalar_t__ anomaly_nr; void** anomaly; int /*<<< orphan*/  anomaly_alloc; } ;
struct TYPE_2__ {int rawsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (void**,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QSORT (void**,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_pack_index_ptr (struct packed_git*,int const*) ; 
 int /*<<< orphan*/  cmp_uint32 ; 
 void* ntohl (int const) ; 
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static void read_v2_anomalous_offsets(struct packed_git *p,
				      struct pack_idx_option *opts)
{
	const uint32_t *idx1, *idx2;
	uint32_t i;
	const uint32_t hashwords = the_hash_algo->rawsz / sizeof(uint32_t);

	/* The address of the 4-byte offset table */
	idx1 = (((const uint32_t *)p->index_data)
		+ 2 /* 8-byte header */
		+ 256 /* fan out */
		+ hashwords * p->num_objects /* object ID table */
		+ p->num_objects /* CRC32 table */
		);

	/* The address of the 8-byte offset table */
	idx2 = idx1 + p->num_objects;

	for (i = 0; i < p->num_objects; i++) {
		uint32_t off = ntohl(idx1[i]);
		if (!(off & 0x80000000))
			continue;
		off = off & 0x7fffffff;
		check_pack_index_ptr(p, &idx2[off * 2]);
		if (idx2[off * 2])
			continue;
		/*
		 * The real offset is ntohl(idx2[off * 2]) in high 4
		 * octets, and ntohl(idx2[off * 2 + 1]) in low 4
		 * octets.  But idx2[off * 2] is Zero!!!
		 */
		ALLOC_GROW(opts->anomaly, opts->anomaly_nr + 1, opts->anomaly_alloc);
		opts->anomaly[opts->anomaly_nr++] = ntohl(idx2[off * 2 + 1]);
	}

	QSORT(opts->anomaly, opts->anomaly_nr, cmp_uint32);
}