#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* add_score ) (int /*<<< orphan*/ ,int,double) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  userdata; TYPE_1__ hooks; } ;
typedef  TYPE_2__ DeepmindContext ;

/* Variables and functions */
 TYPE_2__* dmlab_context () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,double) ; 

__attribute__((used)) static void call_add_score(int player_id, double score) {
  DeepmindContext* ctx = dmlab_context();
  ctx->hooks.add_score(ctx->userdata, player_id, score);
}