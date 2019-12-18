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
struct scanreq {int /*<<< orphan*/  space; } ;
struct ieee80211_scan_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ scan_space (struct ieee80211_scan_entry const*,int*) ; 

__attribute__((used)) static void
get_scan_space(void *arg, const struct ieee80211_scan_entry *se)
{
	struct scanreq *req = arg;
	int ielen;

	req->space += scan_space(se, &ielen);
}