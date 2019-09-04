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
 unsigned int CONVERT_STAT_BITS_BIN ; 
 unsigned int CONVERT_STAT_BITS_TXT_CRLF ; 
 int /*<<< orphan*/  free (void*) ; 
 unsigned int gather_convert_stats (void*,unsigned long) ; 
 char* memchr (void*,char,unsigned long) ; 
 void* read_blob_data_from_index (struct index_state const*,char const*,unsigned long*) ; 

__attribute__((used)) static int has_crlf_in_index(const struct index_state *istate, const char *path)
{
	unsigned long sz;
	void *data;
	const char *crp;
	int has_crlf = 0;

	data = read_blob_data_from_index(istate, path, &sz);
	if (!data)
		return 0;

	crp = memchr(data, '\r', sz);
	if (crp) {
		unsigned int ret_stats;
		ret_stats = gather_convert_stats(data, sz);
		if (!(ret_stats & CONVERT_STAT_BITS_BIN) &&
		    (ret_stats & CONVERT_STAT_BITS_TXT_CRLF))
			has_crlf = 1;
	}
	free(data);
	return has_crlf;
}