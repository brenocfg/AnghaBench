#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  key_id; } ;
typedef  TYPE_1__ lmo_entry_t ;
struct TYPE_6__ {int length; TYPE_1__* index; } ;
typedef  TYPE_2__ lmo_archive_t ;

/* Variables and functions */
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static lmo_entry_t * lmo_find_entry(lmo_archive_t *ar, uint32_t hash)
{
	unsigned int m, l, r;
	uint32_t k;

	l = 0;
	r = ar->length - 1;

	while (1)
	{
		m = l + ((r - l) / 2);

		if (r < l)
			break;

		k = ntohl(ar->index[m].key_id);

		if (k == hash)
			return &ar->index[m];

		if (k > hash)
		{
			if (!m)
				break;

			r = m - 1;
		}
		else
		{
			l = m + 1;
		}
	}

	return NULL;
}