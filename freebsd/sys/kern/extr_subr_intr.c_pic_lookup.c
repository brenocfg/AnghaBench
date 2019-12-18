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
struct intr_pic {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pic_list_lock ; 
 struct intr_pic* pic_lookup_locked (int /*<<< orphan*/ ,intptr_t,int) ; 

__attribute__((used)) static struct intr_pic *
pic_lookup(device_t dev, intptr_t xref, int flags)
{
	struct intr_pic *pic;

	mtx_lock(&pic_list_lock);
	pic = pic_lookup_locked(dev, xref, flags);
	mtx_unlock(&pic_list_lock);
	return (pic);
}