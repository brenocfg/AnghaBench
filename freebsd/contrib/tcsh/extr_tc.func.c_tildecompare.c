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
struct tildecache {int /*<<< orphan*/  user; } ;

/* Variables and functions */
 int Strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tildecompare(const void *xp1, const void *xp2)
{
    const struct tildecache *p1, *p2;

    p1 = xp1;
    p2 = xp2;
    return Strcmp(p1->user, p2->user);
}