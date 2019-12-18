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
struct packet_writer {int dummy; } ;
struct object_array {int nr; TYPE_1__* objects; } ;
struct object {int /*<<< orphan*/  oid; } ;
struct TYPE_2__ {struct object* item; } ;

/* Variables and functions */
 int ALLOW_REACHABLE_SHA1 ; 
 int allow_unadvertised_object_request ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  has_unreachable (struct object_array*) ; 
 int /*<<< orphan*/  is_our_ref (struct object*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_writer_error (struct packet_writer*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stateless_rpc ; 

__attribute__((used)) static void check_non_tip(struct object_array *want_obj,
			  struct packet_writer *writer)
{
	int i;

	/*
	 * In the normal in-process case without
	 * uploadpack.allowReachableSHA1InWant,
	 * non-tip requests can never happen.
	 */
	if (!stateless_rpc && !(allow_unadvertised_object_request & ALLOW_REACHABLE_SHA1))
		goto error;
	if (!has_unreachable(want_obj))
		/* All the non-tip ones are ancestors of what we advertised */
		return;

error:
	/* Pick one of them (we know there at least is one) */
	for (i = 0; i < want_obj->nr; i++) {
		struct object *o = want_obj->objects[i].item;
		if (!is_our_ref(o)) {
			packet_writer_error(writer,
					    "upload-pack: not our ref %s",
					    oid_to_hex(&o->oid));
			die("git upload-pack: not our ref %s",
			    oid_to_hex(&o->oid));
		}
	}
}