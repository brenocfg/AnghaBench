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
struct xml_ctx {int /*<<< orphan*/  name; scalar_t__ userData; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAV_CTX_LOCKENTRY ; 
 int /*<<< orphan*/  DAV_CTX_LOCKTYPE_EXCLUSIVE ; 
 int /*<<< orphan*/  DAV_CTX_LOCKTYPE_WRITE ; 
 int DAV_LOCK_OK ; 
 int DAV_PROP_LOCKEX ; 
 int DAV_PROP_LOCKWR ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_lockprop_ctx(struct xml_ctx *ctx, int tag_closed)
{
	int *lock_flags = (int *)ctx->userData;

	if (tag_closed) {
		if (!strcmp(ctx->name, DAV_CTX_LOCKENTRY)) {
			if ((*lock_flags & DAV_PROP_LOCKEX) &&
			    (*lock_flags & DAV_PROP_LOCKWR)) {
				*lock_flags |= DAV_LOCK_OK;
			}
			*lock_flags &= DAV_LOCK_OK;
		} else if (!strcmp(ctx->name, DAV_CTX_LOCKTYPE_WRITE)) {
			*lock_flags |= DAV_PROP_LOCKWR;
		} else if (!strcmp(ctx->name, DAV_CTX_LOCKTYPE_EXCLUSIVE)) {
			*lock_flags |= DAV_PROP_LOCKEX;
		}
	}
}