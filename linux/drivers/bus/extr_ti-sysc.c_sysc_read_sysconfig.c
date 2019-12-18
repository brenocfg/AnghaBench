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
typedef  int /*<<< orphan*/  u32 ;
struct sysc {int* offsets; } ;

/* Variables and functions */
 size_t SYSC_SYSCONFIG ; 
 int /*<<< orphan*/  sysc_read (struct sysc*,int) ; 

__attribute__((used)) static u32 sysc_read_sysconfig(struct sysc *ddata)
{
	int offset = ddata->offsets[SYSC_SYSCONFIG];

	if (offset < 0)
		return 0;

	return sysc_read(ddata, offset);
}