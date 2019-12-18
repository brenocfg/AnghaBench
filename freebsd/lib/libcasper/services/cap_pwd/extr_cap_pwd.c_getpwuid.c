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
typedef  int /*<<< orphan*/  uid_t ;
struct passwd {int dummy; } ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 struct passwd* cap_getpwcommon (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct passwd *
cap_getpwuid(cap_channel_t *chan, uid_t uid)
{

	return (cap_getpwcommon(chan, "getpwuid", NULL, uid));
}