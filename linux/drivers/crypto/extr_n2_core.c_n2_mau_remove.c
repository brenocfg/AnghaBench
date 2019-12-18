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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct n2_mau {int /*<<< orphan*/  mau_list; } ;

/* Variables and functions */
 struct n2_mau* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_ncp (struct n2_mau*) ; 
 int /*<<< orphan*/  release_global_resources () ; 
 int /*<<< orphan*/  spu_list_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int n2_mau_remove(struct platform_device *dev)
{
	struct n2_mau *mp = dev_get_drvdata(&dev->dev);

	spu_list_destroy(&mp->mau_list);

	release_global_resources();

	free_ncp(mp);

	return 0;
}