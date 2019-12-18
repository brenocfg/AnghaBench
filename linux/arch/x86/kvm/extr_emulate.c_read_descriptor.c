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
typedef  unsigned long u16 ;
struct x86_emulate_ctxt {int dummy; } ;
struct segmented_address {int ea; } ;

/* Variables and functions */
 int X86EMUL_CONTINUE ; 
 int segmented_read_std (struct x86_emulate_ctxt*,struct segmented_address,unsigned long*,int) ; 

__attribute__((used)) static int read_descriptor(struct x86_emulate_ctxt *ctxt,
			   struct segmented_address addr,
			   u16 *size, unsigned long *address, int op_bytes)
{
	int rc;

	if (op_bytes == 2)
		op_bytes = 3;
	*address = 0;
	rc = segmented_read_std(ctxt, addr, size, 2);
	if (rc != X86EMUL_CONTINUE)
		return rc;
	addr.ea += 2;
	rc = segmented_read_std(ctxt, addr, address, op_bytes);
	return rc;
}