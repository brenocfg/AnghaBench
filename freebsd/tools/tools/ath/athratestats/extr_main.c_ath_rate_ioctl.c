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
struct ath_ratestats {int /*<<< orphan*/  re; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCGATHNODERATESTATS ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ath_rate_ioctl(struct ath_ratestats *r)
{

	if (ioctl(r->s, SIOCGATHNODERATESTATS, &r->re) < 0)
		err(1, "ioctl");
}