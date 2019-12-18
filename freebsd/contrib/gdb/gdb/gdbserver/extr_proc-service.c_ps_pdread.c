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
typedef  int /*<<< orphan*/  ps_err_e ;
typedef  int /*<<< orphan*/  paddr_t ;
typedef  int /*<<< orphan*/  gdb_ps_size_t ;
typedef  int /*<<< orphan*/  gdb_ps_read_buf_t ;
typedef  int /*<<< orphan*/  gdb_ps_prochandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  PS_OK ; 
 int /*<<< orphan*/  read_inferior_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ps_err_e
ps_pdread (gdb_ps_prochandle_t ph, paddr_t addr,
	   gdb_ps_read_buf_t buf, gdb_ps_size_t size)
{
  read_inferior_memory (addr, buf, size);
  return PS_OK;
}