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
typedef  int /*<<< orphan*/  linker_file_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  kld_sx ; 
 int /*<<< orphan*/  linker_file_lookup_symbol_internal (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int sx_xlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

caddr_t
linker_file_lookup_symbol(linker_file_t file, const char *name, int deps)
{
	caddr_t sym;
	int locked;

	locked = sx_xlocked(&kld_sx);
	if (!locked)
		sx_xlock(&kld_sx);
	sym = linker_file_lookup_symbol_internal(file, name, deps);
	if (!locked)
		sx_xunlock(&kld_sx);
	return (sym);
}