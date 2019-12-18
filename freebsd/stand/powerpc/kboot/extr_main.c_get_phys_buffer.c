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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {scalar_t__ memsz; size_t bufsz; void* mem; void* buf; } ;

/* Variables and functions */
 void* host_getmem (size_t const) ; 
 TYPE_1__* loaded_segments ; 
 int /*<<< orphan*/  min (size_t const,scalar_t__) ; 
 int nkexec_segments ; 
 scalar_t__ rounddown2 (scalar_t__,size_t const) ; 

__attribute__((used)) static ssize_t
get_phys_buffer(vm_offset_t dest, const size_t len, void **buf)
{
	int i = 0;
	const size_t segsize = 4*1024*1024;

	for (i = 0; i < nkexec_segments; i++) {
		if (dest >= (vm_offset_t)loaded_segments[i].mem &&
		    dest < (vm_offset_t)loaded_segments[i].mem +
		    loaded_segments[i].memsz)
			goto out;
	}

	loaded_segments[nkexec_segments].buf = host_getmem(segsize);
	loaded_segments[nkexec_segments].bufsz = segsize;
	loaded_segments[nkexec_segments].mem = (void *)rounddown2(dest,segsize);
	loaded_segments[nkexec_segments].memsz = segsize;

	i = nkexec_segments;
	nkexec_segments++;

out:
	*buf = loaded_segments[i].buf + (dest -
	    (vm_offset_t)loaded_segments[i].mem);
	return (min(len,loaded_segments[i].bufsz - (dest -
	    (vm_offset_t)loaded_segments[i].mem)));
}