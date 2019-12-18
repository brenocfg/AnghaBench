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
struct proto {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct proto*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct proto*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  protos ; 
 int /*<<< orphan*/  prt_next ; 

void
proto_register(struct proto *proto, bool isdefault)
{
	static bool seen_default = false;

	if (!isdefault)
		TAILQ_INSERT_HEAD(&protos, proto, prt_next);
	else {
		PJDLOG_ASSERT(!seen_default);
		seen_default = true;
		TAILQ_INSERT_TAIL(&protos, proto, prt_next);
	}
}