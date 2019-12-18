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
struct hws_trailer_entry {int clock_base; int /*<<< orphan*/  progusage2; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * tod_clock_base ; 
 scalar_t__ trailer_entry_ptr (unsigned long) ; 

__attribute__((used)) static void aux_sdb_init(unsigned long sdb)
{
	struct hws_trailer_entry *te;

	te = (struct hws_trailer_entry *)trailer_entry_ptr(sdb);

	/* Save clock base */
	te->clock_base = 1;
	memcpy(&te->progusage2, &tod_clock_base[1], 8);
}