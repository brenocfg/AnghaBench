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
struct _citrus_db_locator {scalar_t__ dl_offset; scalar_t__ dl_hashval; } ;

/* Variables and functions */

__attribute__((used)) static __inline void
_citrus_db_locator_init(struct _citrus_db_locator *dl)
{

	dl->dl_hashval = 0;
	dl->dl_offset = 0;
}