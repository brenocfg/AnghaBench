#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hashmap {int /*<<< orphan*/  cmpfn; } ;
struct TYPE_3__ {int /*<<< orphan*/  hash; } ;
struct anonymized_entry {size_t orig_len; void const* anon; size_t anon_len; TYPE_1__ hash; void const* orig; } ;

/* Variables and functions */
 int /*<<< orphan*/  anonymized_entry_cmp ; 
 int /*<<< orphan*/  hash ; 
 int /*<<< orphan*/  hashmap_entry_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct anonymized_entry* hashmap_get_entry (struct hashmap*,struct anonymized_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_init (struct hashmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_put (struct hashmap*,TYPE_1__*) ; 
 int /*<<< orphan*/  memhash (void const*,size_t) ; 
 struct anonymized_entry* xmalloc (int) ; 
 void const* xstrdup (void const*) ; 

__attribute__((used)) static const void *anonymize_mem(struct hashmap *map,
				 void *(*generate)(const void *, size_t *),
				 const void *orig, size_t *len)
{
	struct anonymized_entry key, *ret;

	if (!map->cmpfn)
		hashmap_init(map, anonymized_entry_cmp, NULL, 0);

	hashmap_entry_init(&key.hash, memhash(orig, *len));
	key.orig = orig;
	key.orig_len = *len;
	ret = hashmap_get_entry(map, &key, hash, NULL);

	if (!ret) {
		ret = xmalloc(sizeof(*ret));
		hashmap_entry_init(&ret->hash, key.hash.hash);
		ret->orig = xstrdup(orig);
		ret->orig_len = *len;
		ret->anon = generate(orig, len);
		ret->anon_len = *len;
		hashmap_put(map, &ret->hash);
	}

	*len = ret->anon_len;
	return ret->anon;
}