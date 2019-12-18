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
struct trie {int len; char const* contents; scalar_t__ value; struct trie** children; } ;
typedef  int (* match_fn ) (char const*,scalar_t__,void*) ;

/* Variables and functions */

__attribute__((used)) static int trie_find(struct trie *root, const char *key, match_fn fn,
		     void *baton)
{
	int i;
	int result;
	struct trie *child;

	if (!*key) {
		/* we have reached the end of the key */
		if (root->value && !root->len)
			return fn(key, root->value, baton);
		else
			return -1;
	}

	for (i = 0; i < root->len; i++) {
		/* Partial path normalization: skip consecutive slashes. */
		if (key[i] == '/' && key[i+1] == '/') {
			key++;
			continue;
		}
		if (root->contents[i] != key[i])
			return -1;
	}

	/* Matched the entire compressed section */
	key += i;
	if (!*key) {
		/* End of key */
		if (root->value)
			return fn(key, root->value, baton);
		else
			return -1;
	}

	/* Partial path normalization: skip consecutive slashes */
	while (key[0] == '/' && key[1] == '/')
		key++;

	child = root->children[(unsigned char)*key];
	if (child)
		result = trie_find(child, key + 1, fn, baton);
	else
		result = -1;

	if (result >= 0 || (*key != '/' && *key != 0))
		return result;
	if (root->value)
		return fn(key, root->value, baton);
	else
		return -1;
}