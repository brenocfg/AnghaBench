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

/* Variables and functions */
 int /*<<< orphan*/  LINE_BREAK () ; 
 int /*<<< orphan*/  chaninfo ; 
 int /*<<< orphan*/  getchaninfo (int) ; 
 int /*<<< orphan*/  getregdomain (int) ; 
 int /*<<< orphan*/  print_channels (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  print_regdomain (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  regdomain ; 
 char spacer ; 
 int verbose ; 

__attribute__((used)) static void
list_regdomain(int s, int channelsalso)
{
	getregdomain(s);
	if (channelsalso) {
		getchaninfo(s);
		spacer = ':';
		print_regdomain(&regdomain, 1);
		LINE_BREAK();
		print_channels(s, chaninfo, 1/*allchans*/, 1/*verbose*/);
	} else
		print_regdomain(&regdomain, verbose);
}