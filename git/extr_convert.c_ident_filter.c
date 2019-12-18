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
struct stream_filter {int dummy; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * vtbl; } ;
struct ident_filter {scalar_t__ state; TYPE_1__ filter; int /*<<< orphan*/  left; int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  ident_vtbl ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ident_filter* xmalloc (int) ; 
 int /*<<< orphan*/  xsnprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct stream_filter *ident_filter(const struct object_id *oid)
{
	struct ident_filter *ident = xmalloc(sizeof(*ident));

	xsnprintf(ident->ident, sizeof(ident->ident),
		  ": %s $", oid_to_hex(oid));
	strbuf_init(&ident->left, 0);
	ident->filter.vtbl = &ident_vtbl;
	ident->state = 0;
	return (struct stream_filter *)ident;
}