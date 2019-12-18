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
typedef  int /*<<< orphan*/  uint32_t ;
struct nat64lsn_pgchunk {int dummy; } ;
struct nat64lsn_cfg {int plen4; scalar_t__ pgchunk_delete_delay; struct nat64lsn_alias* aliases; } ;
struct nat64lsn_alias {int tcp_chunkmask; int /*<<< orphan*/ * tcp_pgmask; int /*<<< orphan*/ * tcp; int /*<<< orphan*/  timestamp; } ;

/* Variables and functions */
 scalar_t__ GET_AGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ck_pr_btr_32 (int*,int) ; 
 int /*<<< orphan*/  ck_pr_fence_load () ; 
 scalar_t__ ck_pr_load_32 (int /*<<< orphan*/ *) ; 
 struct nat64lsn_pgchunk* ck_pr_load_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nat64lsn_pgchunk*
nat64lsn_expire_pgchunk(struct nat64lsn_cfg *cfg)
{
#if 0
	struct nat64lsn_alias *alias;
	struct nat64lsn_pgchunk *chunk;
	uint32_t pgmask;
	int i, c;

	for (i = 0; i < 1 << (32 - cfg->plen4); i++) {
		alias = &cfg->aliases[i];
		if (GET_AGE(alias->timestamp) < cfg->pgchunk_delete_delay)
			continue;
		/* Always keep single chunk allocated */
		for (c = 1; c < 32; c++) {
			if ((alias->tcp_chunkmask & (1 << c)) == 0)
				break;
			chunk = ck_pr_load_ptr(&alias->tcp[c]);
			if (ck_pr_load_32(&alias->tcp_pgmask[c]) != 0)
				continue;
			ck_pr_btr_32(&alias->tcp_chunkmask, c);
			ck_pr_fence_load();
			if (ck_pr_load_32(&alias->tcp_pgmask[c]) != 0)
				continue;
		}
	}
#endif
	return (NULL);
}