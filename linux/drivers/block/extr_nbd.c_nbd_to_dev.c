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
struct nbd_device {int /*<<< orphan*/  disk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* disk_to_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct device *nbd_to_dev(struct nbd_device *nbd)
{
	return disk_to_dev(nbd->disk);
}