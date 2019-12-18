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
struct uufsd {int /*<<< orphan*/  d_cg; } ;

/* Variables and functions */
 int cgput (struct uufsd*,int /*<<< orphan*/ *) ; 

int
cgwrite(struct uufsd *disk)
{

	return (cgput(disk, &disk->d_cg));
}