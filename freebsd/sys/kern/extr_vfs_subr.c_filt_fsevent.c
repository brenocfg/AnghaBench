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
struct knote {long kn_fflags; } ;

/* Variables and functions */

__attribute__((used)) static int
filt_fsevent(struct knote *kn, long hint)
{

	kn->kn_fflags |= hint;
	return (kn->kn_fflags != 0);
}