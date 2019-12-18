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
struct tlb {int dummy; } ;
typedef  int dword_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  tlb_read (struct tlb*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  uc_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void _mem_sync(struct tlb *tlb, uc_engine *uc, addr_t addr, dword_t size) {
    char buf[size];
    tlb_read(tlb, addr, buf, size);
    uc_write(uc, addr, buf, size);
}