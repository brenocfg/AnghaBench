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
struct randomdev_hash {int /*<<< orphan*/  sha; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHA256_Update (int /*<<< orphan*/ *,void const*,size_t) ; 

void
randomdev_hash_iterate(struct randomdev_hash *context, const void *data, size_t size)
{

	SHA256_Update(&context->sha, data, size);
}