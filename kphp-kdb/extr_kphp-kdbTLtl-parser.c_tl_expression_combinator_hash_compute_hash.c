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
struct tl_hashmap {int dummy; } ;
struct tl_expression {TYPE_1__* left; } ;
struct TYPE_2__ {int /*<<< orphan*/  text; } ;

/* Variables and functions */
 int /*<<< orphan*/  tl_str_compute_hash (struct tl_hashmap*,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void tl_expression_combinator_hash_compute_hash (struct tl_hashmap *self, void *p, int *h1, int *h2) {
  const struct tl_expression *E = p;
  tl_str_compute_hash (self, E->left->text, h1, h2);
}