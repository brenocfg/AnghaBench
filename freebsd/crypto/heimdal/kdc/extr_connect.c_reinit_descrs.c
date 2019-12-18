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
struct sockaddr {int dummy; } ;
struct descr {int /*<<< orphan*/  __ss; struct sockaddr* sa; } ;

/* Variables and functions */

__attribute__((used)) static void
reinit_descrs (struct descr *d, int n)
{
    int i;

    for (i = 0; i < n; ++i)
	d[i].sa = (struct sockaddr *)&d[i].__ss;
}