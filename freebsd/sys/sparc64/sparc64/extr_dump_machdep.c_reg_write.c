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
typedef  scalar_t__ vm_size_t ;
typedef  int /*<<< orphan*/  vm_paddr_t ;
struct sparc64_dump_reg {int /*<<< orphan*/  dr_offs; scalar_t__ dr_size; int /*<<< orphan*/  dr_pa; } ;
struct dumperinfo {int dummy; } ;
typedef  int /*<<< orphan*/  r ;

/* Variables and functions */
 int dumpsys_buf_write (struct dumperinfo*,char*,int) ; 
 int /*<<< orphan*/  fileofs ; 

__attribute__((used)) static int
reg_write(struct dumperinfo *di, vm_paddr_t pa, vm_size_t size)
{
	struct sparc64_dump_reg r;

	r.dr_pa = pa;
	r.dr_size = size;
	r.dr_offs = fileofs;
	fileofs += size;
	return (dumpsys_buf_write(di, (char *)&r, sizeof(r)));
}