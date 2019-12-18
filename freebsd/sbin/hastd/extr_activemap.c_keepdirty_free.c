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
struct keepdirty {int dummy; } ;
struct activemap {scalar_t__ am_nkeepdirty; int /*<<< orphan*/  am_keepdirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 struct keepdirty* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct keepdirty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct keepdirty*) ; 
 int /*<<< orphan*/  kd_next ; 

__attribute__((used)) static void
keepdirty_free(struct activemap *amp)
{
	struct keepdirty *kd;

	while ((kd = TAILQ_FIRST(&amp->am_keepdirty)) != NULL) {
		TAILQ_REMOVE(&amp->am_keepdirty, kd, kd_next);
		amp->am_nkeepdirty--;
		free(kd);
	}
	PJDLOG_ASSERT(amp->am_nkeepdirty == 0);
}