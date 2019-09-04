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

/* Variables and functions */
 long long CLUSTER_MASK ; 
 int /*<<< orphan*/  cluster_tree ; 
 long long* clusters ; 
 scalar_t__ clusters_num ; 
 int /*<<< orphan*/  lrand48 () ; 
 int /*<<< orphan*/  tree_insert (int /*<<< orphan*/ ,long long,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vkprintf (int,char*,long long) ; 

void add_cluster (long long id) {
  vkprintf (2, "adding cluster with id = %lld\n", id & CLUSTER_MASK);
  clusters[clusters_num ++] = id & CLUSTER_MASK;
  cluster_tree = tree_insert (cluster_tree, id & CLUSTER_MASK, lrand48 (), clusters_num - 1);
}