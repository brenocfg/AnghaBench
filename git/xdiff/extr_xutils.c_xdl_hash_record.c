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

/* Variables and functions */
 long XDF_WHITESPACE_FLAGS ; 
 unsigned long xdl_hash_record_with_whitespace (char const**,char const*,long) ; 

unsigned long xdl_hash_record(char const **data, char const *top, long flags) {
	unsigned long ha = 5381;
	char const *ptr = *data;

	if (flags & XDF_WHITESPACE_FLAGS)
		return xdl_hash_record_with_whitespace(data, top, flags);

	for (; ptr < top && *ptr != '\n'; ptr++) {
		ha += (ha << 5);
		ha ^= (unsigned long) *ptr;
	}
	*data = ptr < top ? ptr + 1: ptr;

	return ha;
}