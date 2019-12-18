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
typedef  int uint64_t ;
struct vmctx {int dummy; } ;

/* Variables and functions */
 int MEM_F_WRITE ; 
 int vga_mem_rd_handler (struct vmctx*,int,void*) ; 
 int /*<<< orphan*/  vga_mem_wr_handler (struct vmctx*,int,int,void*) ; 

__attribute__((used)) static int
vga_mem_handler(struct vmctx *ctx, int vcpu, int dir, uint64_t addr,
		int size, uint64_t *val, void *arg1, long arg2)
{
	if (dir == MEM_F_WRITE) {
		switch (size) {
		case 1:
			vga_mem_wr_handler(ctx, addr, *val, arg1);
			break;
		case 2:
			vga_mem_wr_handler(ctx, addr, *val, arg1);
			vga_mem_wr_handler(ctx, addr + 1, *val >> 8, arg1);
			break;
		case 4:
			vga_mem_wr_handler(ctx, addr, *val, arg1);
			vga_mem_wr_handler(ctx, addr + 1, *val >> 8, arg1);
			vga_mem_wr_handler(ctx, addr + 2, *val >> 16, arg1);
			vga_mem_wr_handler(ctx, addr + 3, *val >> 24, arg1);
			break;
		case 8:
			vga_mem_wr_handler(ctx, addr, *val, arg1);
			vga_mem_wr_handler(ctx, addr + 1, *val >> 8, arg1);
			vga_mem_wr_handler(ctx, addr + 2, *val >> 16, arg1);
			vga_mem_wr_handler(ctx, addr + 3, *val >> 24, arg1);
			vga_mem_wr_handler(ctx, addr + 4, *val >> 32, arg1);
			vga_mem_wr_handler(ctx, addr + 5, *val >> 40, arg1);
			vga_mem_wr_handler(ctx, addr + 6, *val >> 48, arg1);
			vga_mem_wr_handler(ctx, addr + 7, *val >> 56, arg1);
			break;
		}
	} else {
		switch (size) {
		case 1:
			*val = vga_mem_rd_handler(ctx, addr, arg1);
			break;
		case 2:
			*val = vga_mem_rd_handler(ctx, addr, arg1);
			*val |= vga_mem_rd_handler(ctx, addr + 1, arg1) << 8;
			break;
		case 4:
			*val = vga_mem_rd_handler(ctx, addr, arg1);
			*val |= vga_mem_rd_handler(ctx, addr + 1, arg1) << 8;
			*val |= vga_mem_rd_handler(ctx, addr + 2, arg1) << 16;
			*val |= vga_mem_rd_handler(ctx, addr + 3, arg1) << 24;
			break;
		case 8:
			*val = vga_mem_rd_handler(ctx, addr, arg1);
			*val |= vga_mem_rd_handler(ctx, addr + 1, arg1) << 8;
			*val |= vga_mem_rd_handler(ctx, addr + 2, arg1) << 16;
			*val |= vga_mem_rd_handler(ctx, addr + 3, arg1) << 24;
			*val |= vga_mem_rd_handler(ctx, addr + 4, arg1) << 32;
			*val |= vga_mem_rd_handler(ctx, addr + 5, arg1) << 40;
			*val |= vga_mem_rd_handler(ctx, addr + 6, arg1) << 48;
			*val |= vga_mem_rd_handler(ctx, addr + 7, arg1) << 56;
			break;
		}
	}

	return (0);
}