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
struct inode_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  inode_release (struct inode_data*) ; 

__attribute__((used)) static void inode_release_if_exist(struct inode_data *inode) {
    if (inode != NULL)
        inode_release(inode);
}