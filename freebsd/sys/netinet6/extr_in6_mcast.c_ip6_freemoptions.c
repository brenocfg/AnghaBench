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
struct ip6_moptions {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  inp_gcmoptions (struct ip6_moptions*) ; 

void
ip6_freemoptions(struct ip6_moptions *imo)
{
	if (imo == NULL)
		return;
	inp_gcmoptions(imo);
}