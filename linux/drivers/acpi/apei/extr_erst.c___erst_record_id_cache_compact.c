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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {int len; scalar_t__* entries; scalar_t__ refcount; } ;

/* Variables and functions */
 scalar_t__ APEI_ERST_INVALID_RECORD_ID ; 
 TYPE_1__ erst_record_id_cache ; 

__attribute__((used)) static void __erst_record_id_cache_compact(void)
{
	int i, wpos = 0;
	u64 *entries;

	if (erst_record_id_cache.refcount)
		return;

	entries = erst_record_id_cache.entries;
	for (i = 0; i < erst_record_id_cache.len; i++) {
		if (entries[i] == APEI_ERST_INVALID_RECORD_ID)
			continue;
		if (wpos != i)
			entries[wpos] = entries[i];
		wpos++;
	}
	erst_record_id_cache.len = wpos;
}