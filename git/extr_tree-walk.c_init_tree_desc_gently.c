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
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int init_tree_desc_internal (struct tree_desc*,void const*,unsigned long,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

int init_tree_desc_gently(struct tree_desc *desc, const void *buffer, unsigned long size)
{
	struct strbuf err = STRBUF_INIT;
	int result = init_tree_desc_internal(desc, buffer, size, &err);
	if (result)
		error("%s", err.buf);
	strbuf_release(&err);
	return result;
}