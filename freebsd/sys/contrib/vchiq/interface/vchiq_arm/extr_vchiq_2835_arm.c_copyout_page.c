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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,size_t) ; 
 scalar_t__ pmap_quick_enter_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_quick_remove_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
copyout_page(vm_page_t p, size_t offset, void *kaddr, size_t size)
{
        uint8_t *dst;

        dst = (uint8_t*)pmap_quick_enter_page(p);
        if (!dst)
                return ENOMEM;

        memcpy(dst + offset, kaddr, size);

        pmap_quick_remove_page((vm_offset_t)dst);

        return 0;
}