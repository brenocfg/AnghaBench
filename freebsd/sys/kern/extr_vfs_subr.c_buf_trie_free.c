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
struct pctrie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_trie_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
buf_trie_free(struct pctrie *ptree, void *node)
{

	uma_zfree(buf_trie_zone, node);
}