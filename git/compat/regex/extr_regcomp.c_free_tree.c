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
typedef  int /*<<< orphan*/  reg_errcode_t ;
struct TYPE_3__ {int /*<<< orphan*/  token; } ;
typedef  TYPE_1__ bin_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  REG_NOERROR ; 
 int /*<<< orphan*/  free_token (int /*<<< orphan*/ *) ; 

__attribute__((used)) static reg_errcode_t
free_tree (void *extra, bin_tree_t *node)
{
  free_token (&node->token);
  return REG_NOERROR;
}