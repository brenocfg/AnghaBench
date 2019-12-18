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

/* Variables and functions */
 int _wind_combining_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  canonical_reorder_sequence (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
canonical_reorder(uint32_t *tmp, size_t tmp_len)
{
    size_t i;

    for (i = 0; i < tmp_len; ++i) {
	int cc = _wind_combining_class(tmp[i]);
	if (cc) {
	    size_t j;
	    for (j = i + 1;
		 j < tmp_len && _wind_combining_class(tmp[j]);
		 ++j)
		;
	    canonical_reorder_sequence(&tmp[i], j - i);
	    i = j;
	}
    }
}