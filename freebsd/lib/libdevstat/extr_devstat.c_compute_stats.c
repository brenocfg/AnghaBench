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
typedef  int /*<<< orphan*/  u_int64_t ;
struct devstat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSM_BLOCKS_PER_SECOND ; 
 int /*<<< orphan*/  DSM_KB_PER_TRANSFER ; 
 int /*<<< orphan*/  DSM_MB_PER_SECOND ; 
 int /*<<< orphan*/  DSM_MS_PER_TRANSACTION ; 
 int /*<<< orphan*/  DSM_NONE ; 
 int /*<<< orphan*/  DSM_SKIP ; 
 int /*<<< orphan*/  DSM_TOTAL_BLOCKS ; 
 int /*<<< orphan*/  DSM_TOTAL_BYTES ; 
 int /*<<< orphan*/  DSM_TOTAL_TRANSFERS ; 
 int /*<<< orphan*/  DSM_TRANSFERS_PER_SECOND ; 
 int devstat_compute_statistics (struct devstat*,struct devstat*,long double,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,long double*,int /*<<< orphan*/ ,long double*,int /*<<< orphan*/ ,long double*,int /*<<< orphan*/ ,long double*,int /*<<< orphan*/ ,long double*,int /*<<< orphan*/ ) ; 

int
compute_stats(struct devstat *current, struct devstat *previous,
	      long double etime, u_int64_t *total_bytes,
	      u_int64_t *total_transfers, u_int64_t *total_blocks,
	      long double *kb_per_transfer, long double *transfers_per_second,
	      long double *mb_per_second, long double *blocks_per_second,
	      long double *ms_per_transaction)
{
	return(devstat_compute_statistics(current, previous, etime,
	       total_bytes ? DSM_TOTAL_BYTES : DSM_SKIP,
	       total_bytes,
	       total_transfers ? DSM_TOTAL_TRANSFERS : DSM_SKIP,
	       total_transfers,
	       total_blocks ? DSM_TOTAL_BLOCKS : DSM_SKIP,
	       total_blocks,
	       kb_per_transfer ? DSM_KB_PER_TRANSFER : DSM_SKIP,
	       kb_per_transfer,
	       transfers_per_second ? DSM_TRANSFERS_PER_SECOND : DSM_SKIP,
	       transfers_per_second,
	       mb_per_second ? DSM_MB_PER_SECOND : DSM_SKIP,
	       mb_per_second,
	       blocks_per_second ? DSM_BLOCKS_PER_SECOND : DSM_SKIP,
	       blocks_per_second,
	       ms_per_transaction ? DSM_MS_PER_TRANSACTION : DSM_SKIP,
	       ms_per_transaction,
	       DSM_NONE));
}