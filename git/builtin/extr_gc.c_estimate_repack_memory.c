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
typedef  size_t uint64_t ;
struct tree {int dummy; } ;
struct revindex_entry {int dummy; } ;
struct packed_git {size_t pack_size; size_t index_size; } ;
struct object_entry {int dummy; } ;
struct object {int dummy; } ;
struct blob {int dummy; } ;

/* Variables and functions */
 unsigned long approximate_object_count () ; 
 scalar_t__ delta_base_cache_limit ; 
 scalar_t__ max_delta_cache_size ; 

__attribute__((used)) static uint64_t estimate_repack_memory(struct packed_git *pack)
{
	unsigned long nr_objects = approximate_object_count();
	size_t os_cache, heap;

	if (!pack || !nr_objects)
		return 0;

	/*
	 * First we have to scan through at least one pack.
	 * Assume enough room in OS file cache to keep the entire pack
	 * or we may accidentally evict data of other processes from
	 * the cache.
	 */
	os_cache = pack->pack_size + pack->index_size;
	/* then pack-objects needs lots more for book keeping */
	heap = sizeof(struct object_entry) * nr_objects;
	/*
	 * internal rev-list --all --objects takes up some memory too,
	 * let's say half of it is for blobs
	 */
	heap += sizeof(struct blob) * nr_objects / 2;
	/*
	 * and the other half is for trees (commits and tags are
	 * usually insignificant)
	 */
	heap += sizeof(struct tree) * nr_objects / 2;
	/* and then obj_hash[], underestimated in fact */
	heap += sizeof(struct object *) * nr_objects;
	/* revindex is used also */
	heap += sizeof(struct revindex_entry) * nr_objects;
	/*
	 * read_sha1_file() (either at delta calculation phase, or
	 * writing phase) also fills up the delta base cache
	 */
	heap += delta_base_cache_limit;
	/* and of course pack-objects has its own delta cache */
	heap += max_delta_cache_size;

	return os_cache + heap;
}