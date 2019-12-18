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
typedef  int u32 ;
struct uniphier_cache_data {int dummy; } ;

/* Variables and functions */
 int UNIPHIER_SSCOQM_S_ALL ; 
 int /*<<< orphan*/  __uniphier_cache_maint_common (struct uniphier_cache_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __uniphier_cache_sync (struct uniphier_cache_data*) ; 

__attribute__((used)) static void __uniphier_cache_maint_all(struct uniphier_cache_data *data,
				       u32 operation)
{
	__uniphier_cache_maint_common(data, 0, 0,
				      UNIPHIER_SSCOQM_S_ALL | operation);

	__uniphier_cache_sync(data);
}