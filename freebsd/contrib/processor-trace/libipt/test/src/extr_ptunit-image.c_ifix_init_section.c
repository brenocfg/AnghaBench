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
typedef  size_t uint8_t ;
struct pt_section {char* filename; int size; int offset; struct ifix_status* status; } ;
struct image_fixture {int dummy; } ;
struct ifix_status {struct image_fixture* ifix; struct ifix_mapping* mapping; scalar_t__ bad_put; scalar_t__ deleted; } ;
struct ifix_mapping {int size; size_t* content; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pt_section*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ifix_init_section(struct pt_section *section, char *filename,
			      struct ifix_status *status,
			      struct ifix_mapping *mapping,
			      struct image_fixture *ifix)
{
	uint8_t i;

	memset(section, 0, sizeof(*section));

	section->filename = filename;
	section->status = status;
	section->size = mapping->size = sizeof(mapping->content);
	section->offset = 0x10;

	for (i = 0; i < mapping->size; ++i)
		mapping->content[i] = i;

	status->deleted = 0;
	status->bad_put = 0;
	status->mapping = mapping;
	status->ifix = ifix;
}