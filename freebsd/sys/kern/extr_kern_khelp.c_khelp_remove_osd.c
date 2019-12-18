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
struct osd {int dummy; } ;
struct helper {int h_flags; int /*<<< orphan*/  h_refcount; int /*<<< orphan*/  h_id; int /*<<< orphan*/  h_zone; } ;

/* Variables and functions */
 int HELPER_NEEDS_OSD ; 
 int /*<<< orphan*/  OSD_KHELP ; 
 int /*<<< orphan*/  osd_del (int /*<<< orphan*/ ,struct osd*,int /*<<< orphan*/ ) ; 
 void* osd_get (int /*<<< orphan*/ ,struct osd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline void
khelp_remove_osd(struct helper *h, struct osd *hosd)
{
	void *hdata;

	if (h->h_flags & HELPER_NEEDS_OSD) {
		/*
		 * If the current helper uses OSD and calling osd_get()
		 * on the helper's h_id returns non-NULL, the helper has
		 * OSD attached to 'hosd' which needs to be cleaned up.
		 */
		hdata = osd_get(OSD_KHELP, hosd, h->h_id);
		if (hdata != NULL) {
			uma_zfree(h->h_zone, hdata);
			osd_del(OSD_KHELP, hosd, h->h_id);
			refcount_release(&h->h_refcount);
		}
	}
}