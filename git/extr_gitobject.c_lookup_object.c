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
struct repository {TYPE_2__* parsed_objects; } ;
struct TYPE_3__ {int /*<<< orphan*/  hash; } ;
struct object {TYPE_1__ oid; } ;
struct TYPE_4__ {unsigned int obj_hash_size; struct object** obj_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP (struct object*,struct object*) ; 
 unsigned int hash_obj (unsigned char const*,unsigned int) ; 
 scalar_t__ hasheq (unsigned char const*,int /*<<< orphan*/ ) ; 

struct object *lookup_object(struct repository *r, const unsigned char *sha1)
{
	unsigned int i, first;
	struct object *obj;

	if (!r->parsed_objects->obj_hash)
		return NULL;

	first = i = hash_obj(sha1, r->parsed_objects->obj_hash_size);
	while ((obj = r->parsed_objects->obj_hash[i]) != NULL) {
		if (hasheq(sha1, obj->oid.hash))
			break;
		i++;
		if (i == r->parsed_objects->obj_hash_size)
			i = 0;
	}
	if (obj && i != first) {
		/*
		 * Move object to where we started to look for it so
		 * that we do not need to walk the hash table the next
		 * time we look for it.
		 */
		SWAP(r->parsed_objects->obj_hash[i],
		     r->parsed_objects->obj_hash[first]);
	}
	return obj;
}