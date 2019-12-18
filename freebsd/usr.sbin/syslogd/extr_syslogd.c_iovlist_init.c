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
struct iovlist {scalar_t__ totalsize; scalar_t__ iovcnt; } ;

/* Variables and functions */

__attribute__((used)) static void
iovlist_init(struct iovlist *il)
{

	il->iovcnt = 0;
	il->totalsize = 0;
}