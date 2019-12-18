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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int dname_count_size_labels (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  log_err (char*,char const*) ; 
 int /*<<< orphan*/ * sldns_str2wire_dname (char const*,size_t*) ; 

int
parse_dname(const char* str, uint8_t** res, size_t* len, int* labs)
{
	*res = sldns_str2wire_dname(str, len);
	*labs = 0;
	if(!*res) {
		log_err("cannot parse name %s", str);
		return 0;
	}
	*labs = dname_count_size_labels(*res, len);
	return 1;
}