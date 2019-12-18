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
typedef  void* vm_size_t ;
typedef  void* vm_offset_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct mem_region {void* mr_size; void* mr_start; } ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  lmb_size ;
typedef  int cell_t ;
typedef  int /*<<< orphan*/  arr ;

/* Variables and functions */
 int OF_finddevice (char*) ; 
 int OF_getencprop (int,char*,int*,int) ; 
 int OF_getproplen (int,char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
parse_drconf_memory(struct mem_region *ofmem, int *msz,
		    struct mem_region *ofavail, int *asz)
{
	phandle_t phandle;
	vm_offset_t base;
	int i, idx, len, lasz, lmsz, res;
	uint32_t flags, lmb_size[2];
	uint32_t *dmem;

	lmsz = *msz;
	lasz = *asz;

	phandle = OF_finddevice("/ibm,dynamic-reconfiguration-memory");
	if (phandle == -1)
		/* No drconf node, return. */
		return (0);

	res = OF_getencprop(phandle, "ibm,lmb-size", lmb_size,
	    sizeof(lmb_size));
	if (res == -1)
		return (0);
	printf("Logical Memory Block size: %d MB\n", lmb_size[1] >> 20);

	/* Parse the /ibm,dynamic-memory.
	   The first position gives the # of entries. The next two words
 	   reflect the address of the memory block. The next four words are
	   the DRC index, reserved, list index and flags.
	   (see PAPR C.6.6.2 ibm,dynamic-reconfiguration-memory)
	   
	    #el  Addr   DRC-idx  res   list-idx  flags
	   -------------------------------------------------
	   | 4 |   8   |   4   |   4   |   4   |   4   |....
	   -------------------------------------------------
	*/

	len = OF_getproplen(phandle, "ibm,dynamic-memory");
	if (len > 0) {

		/* We have to use a variable length array on the stack
		   since we have very limited stack space.
		*/
		cell_t arr[len/sizeof(cell_t)];

		res = OF_getencprop(phandle, "ibm,dynamic-memory", arr,
		    sizeof(arr));
		if (res == -1)
			return (0);

		/* Number of elements */
		idx = arr[0];

		/* First address, in arr[1], arr[2]*/
		dmem = &arr[1];
	
		for (i = 0; i < idx; i++) {
			base = ((uint64_t)dmem[0] << 32) + dmem[1];
			dmem += 4;
			flags = dmem[1];
			/* Use region only if available and not reserved. */
			if ((flags & 0x8) && !(flags & 0x80)) {
				ofmem[lmsz].mr_start = base;
				ofmem[lmsz].mr_size = (vm_size_t)lmb_size[1];
				ofavail[lasz].mr_start = base;
				ofavail[lasz].mr_size = (vm_size_t)lmb_size[1];
				lmsz++;
				lasz++;
			}
			dmem += 2;
		}
	}

	*msz = lmsz;
	*asz = lasz;

	return (1);
}