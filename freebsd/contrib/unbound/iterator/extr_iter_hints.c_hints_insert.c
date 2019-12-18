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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct iter_hints_stub {int /*<<< orphan*/  node; scalar_t__ noprime; struct delegpt* dp; } ;
struct iter_hints {int /*<<< orphan*/  tree; } ;
struct delegpt {int /*<<< orphan*/  name; int /*<<< orphan*/  namelabs; int /*<<< orphan*/  namelen; } ;

/* Variables and functions */
 int /*<<< orphan*/  delegpt_free_mlc (struct delegpt*) ; 
 int /*<<< orphan*/  dname_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct iter_hints_stub*) ; 
 int /*<<< orphan*/  log_err (char*,char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  name_tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hints_insert(struct iter_hints* hints, uint16_t c, struct delegpt* dp,
	int noprime)
{
	struct iter_hints_stub* node = (struct iter_hints_stub*)malloc(
		sizeof(struct iter_hints_stub));
	if(!node) {
		delegpt_free_mlc(dp);
		return 0;
	}
	node->dp = dp;
	node->noprime = (uint8_t)noprime;
	if(!name_tree_insert(&hints->tree, &node->node, dp->name, dp->namelen,
		dp->namelabs, c)) {
		char buf[257];
		dname_str(dp->name, buf);
		log_err("second hints for zone %s ignored.", buf);
		delegpt_free_mlc(dp);
		free(node);
	}
	return 1;
}