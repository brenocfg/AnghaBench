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
typedef  int /*<<< orphan*/  uint64_t ;
struct table_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
ta_fill_mod_fhash(void *ta_state, struct table_info *ti, void *ta_buf,
    uint64_t *pflags)
{

	/* In is not possible to do rehash if we're not holidng WLOCK. */
	return (0);
}