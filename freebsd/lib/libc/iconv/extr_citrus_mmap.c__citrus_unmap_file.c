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
struct _citrus_region {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * _region_head (struct _citrus_region*) ; 
 int /*<<< orphan*/  _region_init (struct _citrus_region*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _region_size (struct _citrus_region*) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
_citrus_unmap_file(struct _citrus_region *r)
{

	if (_region_head(r) != NULL) {
		(void)munmap(_region_head(r), _region_size(r));
		_region_init(r, NULL, 0);
	}
}