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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct dumperinfo {int (* dumper ) (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ;int /*<<< orphan*/  priv; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int dump_check_bounds (struct dumperinfo*,int /*<<< orphan*/ ,size_t) ; 
 int stub1 (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

int
dump_write(struct dumperinfo *di, void *virtual, vm_offset_t physical,
    off_t offset, size_t length)
{
	int error;

	error = dump_check_bounds(di, offset, length);
	if (error != 0)
		return (error);
	return (di->dumper(di->priv, virtual, physical, offset, length));
}