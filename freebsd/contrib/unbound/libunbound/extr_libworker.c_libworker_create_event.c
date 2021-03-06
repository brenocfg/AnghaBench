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
struct ub_event_base {int dummy; } ;
struct ub_ctx {int dummy; } ;
struct libworker {int dummy; } ;

/* Variables and functions */
 struct libworker* libworker_setup (struct ub_ctx*,int /*<<< orphan*/ ,struct ub_event_base*) ; 

struct libworker* libworker_create_event(struct ub_ctx* ctx,
	struct ub_event_base* eb)
{
	return libworker_setup(ctx, 0, eb);
}