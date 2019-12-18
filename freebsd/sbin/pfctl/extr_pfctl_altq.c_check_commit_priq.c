#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ifname; } ;
struct TYPE_3__ {int default_classes; } ;
struct pfctl_altq {TYPE_2__ pa; TYPE_1__ meta; } ;

/* Variables and functions */
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_commit_priq(int dev, int opts, struct pfctl_altq *if_ppa)
{

	/*
	 * check if priq has one default class for this interface
	 */
	if (if_ppa->meta.default_classes != 1) {
		warnx("should have one default queue on %s", if_ppa->pa.ifname);
		return (1);
	}
	return (0);
}