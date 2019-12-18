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
typedef  int u8 ;
struct d0_tper_features {int supported_features; } ;

/* Variables and functions */
 int TPER_SYNC_SUPPORTED ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static bool check_tper(const void *data)
{
	const struct d0_tper_features *tper = data;
	u8 flags = tper->supported_features;

	if (!(flags & TPER_SYNC_SUPPORTED)) {
		pr_debug("TPer sync not supported. flags = %d\n",
			 tper->supported_features);
		return false;
	}

	return true;
}