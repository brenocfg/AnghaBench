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
typedef  int u32 ;

/* Variables and functions */
 int PCIBIOS_SUCCESSFUL ; 
 int* bytemask ; 
 int /*<<< orphan*/  crp_read (int,int*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 

__attribute__((used)) static int local_read_config(int where, int size, u32 *value)
{ 
	u32 n, data;
	pr_debug("local_read_config from %d size %d\n", where, size);
	n = where % 4;
	crp_read(where & ~3, &data);
	*value = (data >> (8*n)) & bytemask[size];
	pr_debug("local_read_config read %#x\n", *value);
	return PCIBIOS_SUCCESSFUL;
}