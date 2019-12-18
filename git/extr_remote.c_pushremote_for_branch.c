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
struct branch {char const* pushremote_name; } ;

/* Variables and functions */
 char const* pushremote_name ; 
 char const* remote_for_branch (struct branch*,int*) ; 

const char *pushremote_for_branch(struct branch *branch, int *explicit)
{
	if (branch && branch->pushremote_name) {
		if (explicit)
			*explicit = 1;
		return branch->pushremote_name;
	}
	if (pushremote_name) {
		if (explicit)
			*explicit = 1;
		return pushremote_name;
	}
	return remote_for_branch(branch, explicit);
}