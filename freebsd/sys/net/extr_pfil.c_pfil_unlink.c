#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pfil_link_args {int pa_flags; } ;
struct pfil_link {int /*<<< orphan*/  link_epoch_ctx; } ;
typedef  TYPE_1__* pfil_hook_t ;
typedef  TYPE_2__* pfil_head_t ;
struct TYPE_7__ {int /*<<< orphan*/  head_nhooksout; int /*<<< orphan*/  head_out; int /*<<< orphan*/  head_nhooksin; int /*<<< orphan*/  head_in; } ;
struct TYPE_6__ {int /*<<< orphan*/  hook_links; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  PFIL_EPOCH ; 
 int PFIL_IN ; 
 int /*<<< orphan*/  PFIL_LOCK_ASSERT () ; 
 int PFIL_OUT ; 
 int /*<<< orphan*/  PFIL_UNLOCK () ; 
 int /*<<< orphan*/  epoch_call (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfil_link_free ; 
 struct pfil_link* pfil_link_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int
pfil_unlink(struct pfil_link_args *pa, pfil_head_t head, pfil_hook_t hook)
{
	struct pfil_link *in, *out;

	PFIL_LOCK_ASSERT();

	if (pa->pa_flags & PFIL_IN) {
		in = pfil_link_remove(&head->head_in, hook);
		if (in != NULL) {
			head->head_nhooksin--;
			hook->hook_links--;
		}
	} else
		in = NULL;
	if (pa->pa_flags & PFIL_OUT) {
		out = pfil_link_remove(&head->head_out, hook);
		if (out != NULL) {
			head->head_nhooksout--;
			hook->hook_links--;
		}
	} else
		out = NULL;
	PFIL_UNLOCK();

	if (in != NULL)
		epoch_call(PFIL_EPOCH, &in->link_epoch_ctx, pfil_link_free);
	if (out != NULL)
		epoch_call(PFIL_EPOCH, &out->link_epoch_ctx, pfil_link_free);

	if (in == NULL && out == NULL)
		return (ENOENT);
	else
		return (0);
}