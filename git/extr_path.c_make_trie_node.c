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
struct trie {void* value; scalar_t__ len; int /*<<< orphan*/  contents; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 struct trie* xcalloc (int,int) ; 
 int /*<<< orphan*/  xmalloc (scalar_t__) ; 

__attribute__((used)) static struct trie *make_trie_node(const char *key, void *value)
{
	struct trie *new_node = xcalloc(1, sizeof(*new_node));
	new_node->len = strlen(key);
	if (new_node->len) {
		new_node->contents = xmalloc(new_node->len);
		memcpy(new_node->contents, key, new_node->len);
	}
	new_node->value = value;
	return new_node;
}