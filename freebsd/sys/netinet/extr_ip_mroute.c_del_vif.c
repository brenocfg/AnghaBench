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
typedef  int /*<<< orphan*/  vifi_t ;

/* Variables and functions */
 int /*<<< orphan*/  VIF_LOCK () ; 
 int /*<<< orphan*/  VIF_UNLOCK () ; 
 int del_vif_locked (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
del_vif(vifi_t vifi)
{
    int cc;

    VIF_LOCK();
    cc = del_vif_locked(vifi);
    VIF_UNLOCK();

    return cc;
}