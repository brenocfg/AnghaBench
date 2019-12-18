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
typedef  int /*<<< orphan*/  res ;
typedef  int /*<<< orphan*/  dword_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  pt_readn (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

dword_t pt_read(int pid, addr_t addr) {
    dword_t res;
    pt_readn(pid, addr, &res, sizeof(res));
    return res;
}