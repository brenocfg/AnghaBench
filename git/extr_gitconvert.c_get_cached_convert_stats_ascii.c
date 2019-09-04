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
struct index_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 char* gather_convert_stats_ascii (void*,unsigned long) ; 
 void* read_blob_data_from_index (struct index_state const*,char const*,unsigned long*) ; 

const char *get_cached_convert_stats_ascii(const struct index_state *istate,
					   const char *path)
{
	const char *ret;
	unsigned long sz;
	void *data = read_blob_data_from_index(istate, path, &sz);
	ret = gather_convert_stats_ascii(data, sz);
	free(data);
	return ret;
}