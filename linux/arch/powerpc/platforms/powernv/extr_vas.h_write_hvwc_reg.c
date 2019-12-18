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
typedef  int /*<<< orphan*/  u64 ;
struct vas_window {void* hvwc_map; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  out_be64 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vas_log_write (struct vas_window*,char*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void write_hvwc_reg(struct vas_window *win, char *name,
			s32 reg, u64 val)
{
	void *regptr;

	regptr = win->hvwc_map + reg;
	vas_log_write(win, name, regptr, val);

	out_be64(regptr, val);
}