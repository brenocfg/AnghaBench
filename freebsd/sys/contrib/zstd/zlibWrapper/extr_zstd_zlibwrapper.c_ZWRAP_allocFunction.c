#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* z_streamp ;
typedef  int /*<<< orphan*/  uInt ;
struct TYPE_2__ {int /*<<< orphan*/  opaque; void* (* zalloc ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 void* stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void* ZWRAP_allocFunction(void* opaque, size_t size)
{
    z_streamp strm = (z_streamp) opaque;
    void* address = strm->zalloc(strm->opaque, 1, (uInt)size);
    /* LOG_WRAPPERC("ZWRAP alloc %p, %d \n", address, (int)size); */
    return address;
}