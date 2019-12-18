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
struct passwd {int dummy; } ;

/* Variables and functions */
 int pw_nisupdate (char const*,struct passwd*,int /*<<< orphan*/ *) ; 

int
addnispwent(const char *path, struct passwd * pwd)
{
	return pw_nisupdate(path, pwd, NULL);
}