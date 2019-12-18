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
struct tree {int dummy; } ;
struct repository {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  empty_tree; } ;

/* Variables and functions */
 struct tree* lookup_tree (struct repository*,int /*<<< orphan*/ ) ; 
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static struct tree *empty_tree(struct repository *r)
{
	return lookup_tree(r, the_hash_algo->empty_tree);
}