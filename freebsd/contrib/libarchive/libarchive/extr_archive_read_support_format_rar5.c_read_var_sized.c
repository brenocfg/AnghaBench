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
typedef  scalar_t__ uint64_t ;
struct archive_read {int dummy; } ;

/* Variables and functions */
 int read_var (struct archive_read*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int read_var_sized(struct archive_read* a, size_t* pvalue,
    size_t* pvalue_len)
{
	uint64_t v;
	uint64_t v_size = 0;

	const int ret = pvalue_len ? read_var(a, &v, &v_size)
				   : read_var(a, &v, NULL);

	if(ret == 1 && pvalue) {
		*pvalue = (size_t) v;
	}

	if(pvalue_len) {
		/* Possible data truncation should be safe. */
		*pvalue_len = (size_t) v_size;
	}

	return ret;
}