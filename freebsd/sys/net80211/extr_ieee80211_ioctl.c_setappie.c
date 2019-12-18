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
struct ieee80211req {int i_len; int /*<<< orphan*/  i_data; } ;
struct ieee80211_appie {int ie_len; int /*<<< orphan*/  ie_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IEEE80211_FREE (struct ieee80211_appie*,int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_MALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IEEE80211_MAX_APPIE ; 
 int /*<<< orphan*/  IEEE80211_M_NOWAIT ; 
 int /*<<< orphan*/  M_80211_NODE_IE ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
setappie(struct ieee80211_appie **aie, const struct ieee80211req *ireq)
{
	struct ieee80211_appie *app = *aie;
	struct ieee80211_appie *napp;
	int error;

	if (ireq->i_len == 0) {		/* delete any existing ie */
		if (app != NULL) {
			*aie = NULL;	/* XXX racey */
			IEEE80211_FREE(app, M_80211_NODE_IE);
		}
		return 0;
	}
	if (!(2 <= ireq->i_len && ireq->i_len <= IEEE80211_MAX_APPIE))
		return EINVAL;
	/*
	 * Allocate a new appie structure and copy in the user data.
	 * When done swap in the new structure.  Note that we do not
	 * guard against users holding a ref to the old structure;
	 * this must be handled outside this code.
	 *
	 * XXX bad bad bad
	 */
	napp = (struct ieee80211_appie *) IEEE80211_MALLOC(
	    sizeof(struct ieee80211_appie) + ireq->i_len, M_80211_NODE_IE,
	    IEEE80211_M_NOWAIT);
	if (napp == NULL)
		return ENOMEM;
	/* XXX holding ic lock */
	error = copyin(ireq->i_data, napp->ie_data, ireq->i_len);
	if (error) {
		IEEE80211_FREE(napp, M_80211_NODE_IE);
		return error;
	}
	napp->ie_len = ireq->i_len;
	*aie = napp;
	if (app != NULL)
		IEEE80211_FREE(app, M_80211_NODE_IE);
	return 0;
}