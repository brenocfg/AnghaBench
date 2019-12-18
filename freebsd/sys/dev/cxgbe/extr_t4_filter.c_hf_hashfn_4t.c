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
struct t4_filter_tuple {int /*<<< orphan*/  dport; int /*<<< orphan*/  sport; int /*<<< orphan*/ * dip; int /*<<< orphan*/ * sip; } ;
struct t4_filter_specification {scalar_t__ type; struct t4_filter_tuple val; } ;

/* Variables and functions */
 int /*<<< orphan*/  FNV1_32_INIT ; 
 int /*<<< orphan*/  fnv_32_buf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t
hf_hashfn_4t(struct t4_filter_specification *fs)
{
	struct t4_filter_tuple *ft = &fs->val;
	uint32_t hash;

	if (fs->type) {
		/* IPv6 */
		hash = fnv_32_buf(&ft->sip[0], 16, FNV1_32_INIT);
		hash = fnv_32_buf(&ft->dip[0], 16, hash);
	} else {
		hash = fnv_32_buf(&ft->sip[0], 4, FNV1_32_INIT);
		hash = fnv_32_buf(&ft->dip[0], 4, hash);
	}
	hash = fnv_32_buf(&ft->sport, sizeof(ft->sport), hash);
	hash = fnv_32_buf(&ft->dport, sizeof(ft->dport), hash);

	return (hash);
}