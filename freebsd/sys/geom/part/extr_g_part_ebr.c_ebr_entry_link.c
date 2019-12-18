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
typedef  scalar_t__ uint32_t ;
typedef  int u_char ;
struct g_part_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ebr_set_chs (struct g_part_table*,scalar_t__,int*,int*,int*) ; 
 int /*<<< orphan*/  le32enc (int*,scalar_t__) ; 

__attribute__((used)) static void
ebr_entry_link(struct g_part_table *table, uint32_t start, uint32_t end,
   u_char *buf)
{

	buf[0] = 0 /* dp_flag */;
	ebr_set_chs(table, start, &buf[3] /* dp_scyl */, &buf[1] /* dp_shd */,
	    &buf[2] /* dp_ssect */);
	buf[4] = 5 /* dp_typ */;
	ebr_set_chs(table, end, &buf[7] /* dp_ecyl */, &buf[5] /* dp_ehd */,
	    &buf[6] /* dp_esect */);
	le32enc(buf + 8, start);
	le32enc(buf + 12, end - start + 1);
}