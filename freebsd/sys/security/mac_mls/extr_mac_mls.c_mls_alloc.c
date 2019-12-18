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
struct mac_mls {int dummy; } ;

/* Variables and functions */
 int M_ZERO ; 
 struct mac_mls* uma_zalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zone_mls ; 

__attribute__((used)) static struct mac_mls *
mls_alloc(int flag)
{

	return (uma_zalloc(zone_mls, flag | M_ZERO));
}