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
struct gpt_hdr {scalar_t__ hdr_revision; scalar_t__ hdr_size; scalar_t__ hdr_lba_start; scalar_t__ hdr_lba_end; scalar_t__ hdr_entries; scalar_t__ hdr_entsz; scalar_t__ hdr_crc_table; int /*<<< orphan*/  hdr_uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EQUUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gpt_matched_hdrs(struct gpt_hdr *pri, struct gpt_hdr *sec)
{

	if (pri == NULL || sec == NULL)
		return (0);

	if (!EQUUID(&pri->hdr_uuid, &sec->hdr_uuid))
		return (0);
	return ((pri->hdr_revision == sec->hdr_revision &&
	    pri->hdr_size == sec->hdr_size &&
	    pri->hdr_lba_start == sec->hdr_lba_start &&
	    pri->hdr_lba_end == sec->hdr_lba_end &&
	    pri->hdr_entries == sec->hdr_entries &&
	    pri->hdr_entsz == sec->hdr_entsz &&
	    pri->hdr_crc_table == sec->hdr_crc_table) ? 1 : 0);
}