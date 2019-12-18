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
struct ata_eh_info {char* desc; scalar_t__ desc_len; } ;

/* Variables and functions */

void ata_ehi_clear_desc(struct ata_eh_info *ehi)
{
	ehi->desc[0] = '\0';
	ehi->desc_len = 0;
}