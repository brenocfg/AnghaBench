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
struct group {int dummy; } ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 struct group* cap_getgrcommon (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct group *
cap_getgrgid(cap_channel_t *chan, gid_t gid)
{

	return (cap_getgrcommon(chan, "getgrgid", NULL, gid));
}