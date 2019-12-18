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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct dcons_buf {int dummy; } ;

/* Variables and functions */
 int DCONS_BUF_SIZE ; 
 int VTOP (char*) ; 
 int /*<<< orphan*/ * dcons_buffer ; 
 int /*<<< orphan*/  dcons_init (struct dcons_buf*,int,int /*<<< orphan*/ ) ; 
 int dcons_paddr ; 
 int dcons_started ; 
 int /*<<< orphan*/  fw_enable () ; 
 scalar_t__ round_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int
dconsole_init(int arg)
{
    char buf[16], *dbuf;
    int size;

    if (dcons_started && arg == 0)
	return 0;
    dcons_started = 1;

    size = DCONS_BUF_SIZE;
    dbuf = (char *)round_page((vm_offset_t)&dcons_buffer[0]);
    dcons_paddr = VTOP(dbuf);
    sprintf(buf, "0x%08x", dcons_paddr);
    setenv("dcons.addr", buf, 1);

    dcons_init((struct dcons_buf *)dbuf, size, sc);
    sprintf(buf, "%d", size);
    setenv("dcons.size", buf, 1);
    fw_enable();
    return(0);
}