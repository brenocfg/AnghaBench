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
struct x86_exception {int dummy; } ;
struct x86_emulate_ctxt {int dummy; } ;

/* Variables and functions */
 int emulator_read_write (struct x86_emulate_ctxt*,unsigned long,void*,unsigned int,struct x86_exception*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_emultor ; 

__attribute__((used)) static int emulator_read_emulated(struct x86_emulate_ctxt *ctxt,
				  unsigned long addr,
				  void *val,
				  unsigned int bytes,
				  struct x86_exception *exception)
{
	return emulator_read_write(ctxt, addr, val, bytes,
				   exception, &read_emultor);
}