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
struct st_h2o_tunnel_t {int /*<<< orphan*/  timeout_entry; int /*<<< orphan*/  timeout; TYPE_1__* ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  loop; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void reset_timeout(struct st_h2o_tunnel_t *tunnel)
{
    h2o_timer_unlink(&tunnel->timeout_entry);
    h2o_timer_link(tunnel->ctx->loop, tunnel->timeout, &tunnel->timeout_entry);
}