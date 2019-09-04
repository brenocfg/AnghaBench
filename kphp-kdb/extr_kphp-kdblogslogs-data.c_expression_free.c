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
struct TYPE_3__ {int /*<<< orphan*/  root; int /*<<< orphan*/  token_list; } ;
typedef  TYPE_1__ expression ;

/* Variables and functions */
 int /*<<< orphan*/  del_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_token_list (int /*<<< orphan*/ ) ; 

void expression_free (expression *e) {
  del_token_list (e->token_list);
  del_node (e->root);
}