#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  extra_words; int /*<<< orphan*/  depth; int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ tree23_root_t ;

/* Variables and functions */
 int /*<<< orphan*/  dump_rec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump (tree23_root_t *R) {
  dump_rec (R->root, R->depth, R->extra_words);
}