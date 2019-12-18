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
struct vc_map {int scd_index; } ;
struct idt77252_dev {int scd_size; unsigned long scd_base; struct vc_map** scd2vc; } ;

/* Variables and functions */
 int SAR_SRAM_SCD_SIZE ; 

__attribute__((used)) static unsigned long
get_free_scd(struct idt77252_dev *card, struct vc_map *vc)
{
	int i;

	for (i = 0; i < card->scd_size; i++) {
		if (!card->scd2vc[i]) {
			card->scd2vc[i] = vc;
			vc->scd_index = i;
			return card->scd_base + i * SAR_SRAM_SCD_SIZE;
		}
	}
	return 0;
}