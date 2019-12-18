#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ class; scalar_t__ len; int /*<<< orphan*/  address; } ;
struct peerid {TYPE_1__ enddisc; int /*<<< orphan*/  authname; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
peerid_Equal(const struct peerid *p1, const struct peerid *p2)
{
  return !strcmp(p1->authname, p2->authname) &&
         p1->enddisc.class == p2->enddisc.class &&
         p1->enddisc.len == p2->enddisc.len &&
         !memcmp(p1->enddisc.address, p2->enddisc.address, p1->enddisc.len);
}