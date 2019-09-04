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
struct tree_desc {unsigned long size; void const* buffer; } ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 int decode_tree_entry (struct tree_desc*,void const*,unsigned long,struct strbuf*) ; 

__attribute__((used)) static int init_tree_desc_internal(struct tree_desc *desc, const void *buffer, unsigned long size, struct strbuf *err)
{
	desc->buffer = buffer;
	desc->size = size;
	if (size)
		return decode_tree_entry(desc, buffer, size, err);
	return 0;
}