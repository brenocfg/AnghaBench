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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTAS_RMOBUF_MAX ; 
 int /*<<< orphan*/  rtas_rmo_buf ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ppc_rtas_rmo_buf_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%016lx %x\n", rtas_rmo_buf, RTAS_RMOBUF_MAX);
	return 0;
}