#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_t ;
struct TYPE_9__ {int /*<<< orphan*/ * zs_buckets_with_n_entries; int /*<<< orphan*/ * zs_entries_using_n_chunks; int /*<<< orphan*/ * zs_blocks_n_tenths_full; int /*<<< orphan*/ * zs_blocks_with_n5_entries; int /*<<< orphan*/ * zs_leafs_with_2n_pointers; } ;
typedef  TYPE_3__ zap_stats_t ;
typedef  int /*<<< orphan*/  zap_leaf_t ;
struct zap_leaf_entry {int le_name_numints; int le_value_numints; int le_value_intlen; int le_next; } ;
struct TYPE_7__ {int zt_shift; } ;
struct TYPE_11__ {TYPE_1__ zap_ptrtbl; } ;
struct TYPE_8__ {int lh_prefix_len; int lh_nentries; int lh_nfree; } ;
struct TYPE_10__ {int* l_hash; TYPE_2__ l_hdr; } ;

/* Variables and functions */
 int CHAIN_END ; 
 int FZAP_BLOCK_SHIFT (int /*<<< orphan*/ *) ; 
 int MIN (int,scalar_t__) ; 
 scalar_t__ ZAP_HISTOGRAM_SIZE ; 
 int ZAP_LEAF_ARRAY_BYTES ; 
 int ZAP_LEAF_ARRAY_NCHUNKS (int) ; 
 struct zap_leaf_entry* ZAP_LEAF_ENTRY (int /*<<< orphan*/ *,int) ; 
 int ZAP_LEAF_HASH_NUMENTRIES (int /*<<< orphan*/ *) ; 
 TYPE_6__* zap_f_phys (int /*<<< orphan*/ *) ; 
 TYPE_5__* zap_leaf_phys (int /*<<< orphan*/ *) ; 

void
zap_leaf_stats(zap_t *zap, zap_leaf_t *l, zap_stats_t *zs)
{
	int n = zap_f_phys(zap)->zap_ptrtbl.zt_shift -
	    zap_leaf_phys(l)->l_hdr.lh_prefix_len;
	n = MIN(n, ZAP_HISTOGRAM_SIZE-1);
	zs->zs_leafs_with_2n_pointers[n]++;


	n = zap_leaf_phys(l)->l_hdr.lh_nentries/5;
	n = MIN(n, ZAP_HISTOGRAM_SIZE-1);
	zs->zs_blocks_with_n5_entries[n]++;

	n = ((1<<FZAP_BLOCK_SHIFT(zap)) -
	    zap_leaf_phys(l)->l_hdr.lh_nfree * (ZAP_LEAF_ARRAY_BYTES+1))*10 /
	    (1<<FZAP_BLOCK_SHIFT(zap));
	n = MIN(n, ZAP_HISTOGRAM_SIZE-1);
	zs->zs_blocks_n_tenths_full[n]++;

	for (int i = 0; i < ZAP_LEAF_HASH_NUMENTRIES(l); i++) {
		int nentries = 0;
		int chunk = zap_leaf_phys(l)->l_hash[i];

		while (chunk != CHAIN_END) {
			struct zap_leaf_entry *le =
			    ZAP_LEAF_ENTRY(l, chunk);

			n = 1 + ZAP_LEAF_ARRAY_NCHUNKS(le->le_name_numints) +
			    ZAP_LEAF_ARRAY_NCHUNKS(le->le_value_numints *
			    le->le_value_intlen);
			n = MIN(n, ZAP_HISTOGRAM_SIZE-1);
			zs->zs_entries_using_n_chunks[n]++;

			chunk = le->le_next;
			nentries++;
		}

		n = nentries;
		n = MIN(n, ZAP_HISTOGRAM_SIZE-1);
		zs->zs_buckets_with_n_entries[n]++;
	}
}