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
struct remotes_hash_key {char const* str; int len; } ;
struct remote {int prune; int prune_tags; int /*<<< orphan*/  hash; int /*<<< orphan*/  fetch; int /*<<< orphan*/  push; int /*<<< orphan*/  name; } ;
struct hashmap_entry {int prune; int prune_tags; int /*<<< orphan*/  hash; int /*<<< orphan*/  fetch; int /*<<< orphan*/  push; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct remote**,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REFSPEC_FETCH ; 
 int /*<<< orphan*/  REFSPEC_PUSH ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_entry_init (struct remote*,int /*<<< orphan*/ ) ; 
 struct remote* hashmap_get (int /*<<< orphan*/ *,struct remote*,struct remotes_hash_key*) ; 
 struct remote* hashmap_put (int /*<<< orphan*/ *,struct remote*) ; 
 int /*<<< orphan*/  init_remotes_hash () ; 
 int /*<<< orphan*/  memhash (char const*,int) ; 
 int /*<<< orphan*/  refspec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct remote** remotes ; 
 int /*<<< orphan*/  remotes_alloc ; 
 int /*<<< orphan*/  remotes_hash ; 
 scalar_t__ remotes_nr ; 
 int strlen (char const*) ; 
 struct remote* xcalloc (int,int) ; 
 int /*<<< orphan*/  xstrndup (char const*,int) ; 

__attribute__((used)) static struct remote *make_remote(const char *name, int len)
{
	struct remote *ret, *replaced;
	struct remotes_hash_key lookup;
	struct hashmap_entry lookup_entry;

	if (!len)
		len = strlen(name);

	init_remotes_hash();
	lookup.str = name;
	lookup.len = len;
	hashmap_entry_init(&lookup_entry, memhash(name, len));

	if ((ret = hashmap_get(&remotes_hash, &lookup_entry, &lookup)) != NULL)
		return ret;

	ret = xcalloc(1, sizeof(struct remote));
	ret->prune = -1;  /* unspecified */
	ret->prune_tags = -1;  /* unspecified */
	ret->name = xstrndup(name, len);
	refspec_init(&ret->push, REFSPEC_PUSH);
	refspec_init(&ret->fetch, REFSPEC_FETCH);

	ALLOC_GROW(remotes, remotes_nr + 1, remotes_alloc);
	remotes[remotes_nr++] = ret;

	hashmap_entry_init(ret, lookup_entry.hash);
	replaced = hashmap_put(&remotes_hash, ret);
	assert(replaced == NULL);  /* no previous entry overwritten */
	return ret;
}