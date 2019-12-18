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
typedef  int uint64_t ;
struct TYPE_2__ {int* cell; } ;
typedef  TYPE_1__ _BIG5EncodingInfo ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static int
_citrus_BIG5_fill_rowcol(void * __restrict ctx, const char * __restrict s,
    uint64_t start, uint64_t end)
{
	_BIG5EncodingInfo *ei;
	uint64_t n;
	int i;

	if (start > 0xFF || end > 0xFF)
		return (EINVAL);
	ei = (_BIG5EncodingInfo *)ctx;
	i = strcmp("row", s) ? 1 : 0;
	i = 1 << i;
	for (n = start; n <= end; ++n)
		ei->cell[n & 0xFF] |= i;
	return (0);
}