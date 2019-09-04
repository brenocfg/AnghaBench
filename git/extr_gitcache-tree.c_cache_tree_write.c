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
struct strbuf {int dummy; } ;
struct cache_tree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_one (struct strbuf*,struct cache_tree*,char*,int /*<<< orphan*/ ) ; 

void cache_tree_write(struct strbuf *sb, struct cache_tree *root)
{
	write_one(sb, root, "", 0);
}