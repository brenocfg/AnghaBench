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
struct iwnstats {int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCZIWNSTATS ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
iwn_zerostats(struct iwnstats *is)
{

	if (ioctl(is->s, SIOCZIWNSTATS, NULL) < 0)
		err(-1, "ioctl");
}