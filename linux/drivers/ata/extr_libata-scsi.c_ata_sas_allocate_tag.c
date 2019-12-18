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
struct ata_port {int sas_last_tag; int /*<<< orphan*/  sas_tag_allocated; TYPE_1__* host; } ;
struct TYPE_2__ {unsigned int n_tags; } ;

/* Variables and functions */
 scalar_t__ ata_tag_internal (unsigned int) ; 
 int /*<<< orphan*/  test_and_set_bit (unsigned int,int /*<<< orphan*/ *) ; 

int ata_sas_allocate_tag(struct ata_port *ap)
{
	unsigned int max_queue = ap->host->n_tags;
	unsigned int i, tag;

	for (i = 0, tag = ap->sas_last_tag + 1; i < max_queue; i++, tag++) {
		tag = tag < max_queue ? tag : 0;

		/* the last tag is reserved for internal command. */
		if (ata_tag_internal(tag))
			continue;

		if (!test_and_set_bit(tag, &ap->sas_tag_allocated)) {
			ap->sas_last_tag = tag;
			return tag;
		}
	}
	return -1;
}