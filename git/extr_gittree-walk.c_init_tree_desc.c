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
struct tree_desc {int dummy; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ init_tree_desc_internal (struct tree_desc*,void const*,unsigned long,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

void init_tree_desc(struct tree_desc *desc, const void *buffer, unsigned long size)
{
	struct strbuf err = STRBUF_INIT;
	if (init_tree_desc_internal(desc, buffer, size, &err))
		die("%s", err.buf);
	strbuf_release(&err);
}