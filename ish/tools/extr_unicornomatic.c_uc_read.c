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
typedef  int /*<<< orphan*/  uc_engine ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  uc_mem_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  uc_trycall (int /*<<< orphan*/ ,char*) ; 

void uc_read(uc_engine *uc, addr_t addr, void *buf, size_t size) {
    uc_trycall(uc_mem_read(uc, addr, buf, size), "uc_read");
}