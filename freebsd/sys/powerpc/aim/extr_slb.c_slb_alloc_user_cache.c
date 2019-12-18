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
struct slb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_ZERO ; 
 int /*<<< orphan*/  slb_cache_zone ; 
 struct slb** uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct slb **
slb_alloc_user_cache(void)
{
	return (uma_zalloc(slb_cache_zone, M_ZERO));
}