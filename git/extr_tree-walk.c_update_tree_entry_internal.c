#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pathlen; scalar_t__ path; } ;
struct tree_desc {void* buffer; unsigned long size; TYPE_1__ entry; } ;
struct strbuf {int dummy; } ;
struct TYPE_4__ {int rawsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int decode_tree_entry (struct tree_desc*,void const*,unsigned long,struct strbuf*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 TYPE_2__* the_hash_algo ; 

__attribute__((used)) static int update_tree_entry_internal(struct tree_desc *desc, struct strbuf *err)
{
	const void *buf = desc->buffer;
	const unsigned char *end = (const unsigned char *)desc->entry.path + desc->entry.pathlen + 1 + the_hash_algo->rawsz;
	unsigned long size = desc->size;
	unsigned long len = end - (const unsigned char *)buf;

	if (size < len)
		die(_("too-short tree file"));
	buf = end;
	size -= len;
	desc->buffer = buf;
	desc->size = size;
	if (size)
		return decode_tree_entry(desc, buf, size, err);
	return 0;
}