#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ node_t ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_MAGIC ; 
 int /*<<< orphan*/  assert_u32_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int node_cmp (TYPE_1__ const*,TYPE_1__ const*) ; 

__attribute__((used)) static int
node_cmp_magic(const node_t *a, const node_t *b) {

	assert_u32_eq(a->magic, NODE_MAGIC, "Bad magic");
	assert_u32_eq(b->magic, NODE_MAGIC, "Bad magic");

	return node_cmp(a, b);
}