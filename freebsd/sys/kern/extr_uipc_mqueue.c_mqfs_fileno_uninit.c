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
struct unrhdr {int dummy; } ;
struct mqfs_info {struct unrhdr* mi_unrhdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_unrhdr (struct unrhdr*) ; 

__attribute__((used)) static void
mqfs_fileno_uninit(struct mqfs_info *mi)
{
	struct unrhdr *up;

	up = mi->mi_unrhdr;
	mi->mi_unrhdr = NULL;
	delete_unrhdr(up);
}