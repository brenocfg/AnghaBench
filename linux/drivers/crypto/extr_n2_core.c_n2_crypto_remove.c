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
struct n2_crypto {int /*<<< orphan*/  cwq_list; } ;

/* Variables and functions */
 struct n2_crypto* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_n2cp (struct n2_crypto*) ; 
 int /*<<< orphan*/  n2_unregister_algs () ; 
 int /*<<< orphan*/  release_global_resources () ; 
 int /*<<< orphan*/  spu_list_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int n2_crypto_remove(struct platform_device *dev)
{
	struct n2_crypto *np = dev_get_drvdata(&dev->dev);

	n2_unregister_algs();

	spu_list_destroy(&np->cwq_list);

	release_global_resources();

	free_n2cp(np);

	return 0;
}