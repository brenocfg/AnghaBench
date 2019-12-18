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
typedef  int /*<<< orphan*/  u32 ;
struct ata_link {int /*<<< orphan*/  ap; } ;

/* Variables and functions */
 int sata_oxnas_scr_write_port (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sata_oxnas_scr_write(struct ata_link *link, unsigned int sc_reg,
				u32 val)
{
	return sata_oxnas_scr_write_port(link->ap, sc_reg, val);
}