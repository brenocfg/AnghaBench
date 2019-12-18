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
struct drm_fb_helper {int /*<<< orphan*/  kernel_fb_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_notifier_chain_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_helper_crtc_free (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  kernel_fb_helper_list ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic_notifier_list ; 
 int /*<<< orphan*/  paniced ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  sysrq_drm_fb_helper_restore_op ; 
 int /*<<< orphan*/  unregister_sysrq_key (char,int /*<<< orphan*/ *) ; 

void drm_fb_helper_fini(struct drm_fb_helper *fb_helper)
{
	if (!list_empty(&fb_helper->kernel_fb_list)) {
		list_del(&fb_helper->kernel_fb_list);
#if 0 && defined(FREEBSD_NOTYET)
		if (list_empty(&kernel_fb_helper_list)) {
			pr_info("drm: unregistered panic notifier\n");
			atomic_notifier_chain_unregister(&panic_notifier_list,
							 &paniced);
			unregister_sysrq_key('v', &sysrq_drm_fb_helper_restore_op);
		}
#endif /* FREEBSD_NOTYET */
	}

	drm_fb_helper_crtc_free(fb_helper);

}