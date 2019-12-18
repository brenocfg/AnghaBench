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
typedef  int /*<<< orphan*/  u_long ;
struct ieee80211com {int dummy; } ;

/* Variables and functions */
 int ENOTTY ; 

__attribute__((used)) static int
iwn_ioctl(struct ieee80211com *ic, u_long cmd, void *data)
{

	return (ENOTTY);
}