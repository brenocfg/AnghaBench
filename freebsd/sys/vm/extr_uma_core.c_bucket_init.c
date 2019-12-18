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
struct uma_bucket_zone {int ubz_entries; int /*<<< orphan*/  ubz_name; int /*<<< orphan*/  ubz_zone; } ;
struct uma_bucket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int UMA_ZFLAG_BUCKET ; 
 int UMA_ZONE_MTXCLASS ; 
 int UMA_ZONE_NUMA ; 
 struct uma_bucket_zone* bucket_zones ; 
 int roundup (int,int) ; 
 int /*<<< orphan*/  uma_zcreate (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bucket_init(void)
{
	struct uma_bucket_zone *ubz;
	int size;

	for (ubz = &bucket_zones[0]; ubz->ubz_entries != 0; ubz++) {
		size = roundup(sizeof(struct uma_bucket), sizeof(void *));
		size += sizeof(void *) * ubz->ubz_entries;
		ubz->ubz_zone = uma_zcreate(ubz->ubz_name, size,
		    NULL, NULL, NULL, NULL, UMA_ALIGN_PTR,
		    UMA_ZONE_MTXCLASS | UMA_ZFLAG_BUCKET | UMA_ZONE_NUMA);
	}
}