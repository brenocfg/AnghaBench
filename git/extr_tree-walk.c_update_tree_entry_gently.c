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
struct tree_desc {scalar_t__ size; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ update_tree_entry_internal (struct tree_desc*,struct strbuf*) ; 

int update_tree_entry_gently(struct tree_desc *desc)
{
	struct strbuf err = STRBUF_INIT;
	if (update_tree_entry_internal(desc, &err)) {
		error("%s", err.buf);
		strbuf_release(&err);
		/* Stop processing this tree after error */
		desc->size = 0;
		return -1;
	}
	strbuf_release(&err);
	return 0;
}