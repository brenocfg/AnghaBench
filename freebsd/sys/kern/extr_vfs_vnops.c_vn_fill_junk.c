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
struct kinfo_file {int /*<<< orphan*/ * kf_path; } ;

/* Variables and functions */
 int arc4random () ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
vn_fill_junk(struct kinfo_file *kif)
{
	size_t len, olen;

	/*
	 * Simulate vn_fullpath returning changing values for a given
	 * vp during e.g. coredump.
	 */
	len = (arc4random() % (sizeof(kif->kf_path) - 2)) + 1;
	olen = strlen(kif->kf_path);
	if (len < olen)
		strcpy(&kif->kf_path[len - 1], "$");
	else
		for (; olen < len; olen++)
			strcpy(&kif->kf_path[olen], "A");
}