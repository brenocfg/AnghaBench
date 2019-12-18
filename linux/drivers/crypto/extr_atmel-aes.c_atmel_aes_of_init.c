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
struct platform_device {int dummy; } ;
struct crypto_platform_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct crypto_platform_data* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct crypto_platform_data *atmel_aes_of_init(struct platform_device *pdev)
{
	return ERR_PTR(-EINVAL);
}