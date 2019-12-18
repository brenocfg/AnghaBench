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
struct el_subpacket_annotation {scalar_t__ class; scalar_t__ type; scalar_t__ revision; char** annotation; int /*<<< orphan*/  description; struct el_subpacket_annotation* next; } ;
struct el_subpacket {scalar_t__ class; scalar_t__ type; scalar_t__ revision; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  err_print_prefix ; 
 int /*<<< orphan*/  mchk_dump_mem (struct el_subpacket*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct el_subpacket_annotation* subpacket_annotation_list ; 

void 
el_annotate_subpacket(struct el_subpacket *header)
{
	struct el_subpacket_annotation *a;
	char **annotation = NULL;

	for (a = subpacket_annotation_list; a; a = a->next) {
		if (a->class == header->class &&
		    a->type == header->type &&
		    a->revision == header->revision) {
			/*
			 * We found the annotation
			 */
			annotation = a->annotation;
			printk("%s  %s\n", err_print_prefix, a->description);
			break;
		}
	}

	mchk_dump_mem(header, header->length, annotation);
}