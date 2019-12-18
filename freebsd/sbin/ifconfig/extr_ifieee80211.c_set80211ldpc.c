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
struct afswtch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_LDPC ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ get80211val (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  set80211 (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set80211ldpc(const char *val, int d, int s, const struct afswtch *rafp)
{
        int ldpc;
 
        if (get80211val(s, IEEE80211_IOC_LDPC, &ldpc) < 0)
                errx(-1, "cannot set LDPC setting");
        if (d < 0) {
                d = -d;
                ldpc &= ~d;
        } else
                ldpc |= d;
        set80211(s, IEEE80211_IOC_LDPC, ldpc, 0, NULL);
}