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
struct fs {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int ffs_sbget (int*,struct fs**,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_pread ; 

int
sbget(int devfd, struct fs **fsp, off_t sblockloc)
{

	return (ffs_sbget(&devfd, fsp, sblockloc, "user", use_pread));
}