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
typedef  int u_int32_t ;
struct au_info {int* x; int* y; int* z; scalar_t__* routes; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AU_CDC_READY ; 
 int AU_IRQ_ENABLE ; 
 int AU_REG_ADB ; 
 int AU_REG_CODECCHN ; 
 int AU_REG_CODECEN ; 
 int AU_REG_CODECST ; 
 int AU_REG_IRQGLOB ; 
 int AU_REG_RTBASE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  au_addroute (struct au_info*,int,int,int) ; 
 int /*<<< orphan*/  au_clrfifo (struct au_info*,int) ; 
 int /*<<< orphan*/  au_encodec (struct au_info*,int) ; 
 int au_rd (struct au_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  au_wr (struct au_info*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
au_init(device_t dev, struct au_info *au)
{
	u_int32_t	i, j;

	au_wr(au, 0, AU_REG_IRQGLOB, 0xffffffff, 4);
	DELAY(100000);

	/* init codec */
	/* cold reset */
	for (i=0; i<32; i++) {
		au_wr(au, 0, AU_REG_CODECCHN+(i<<2), 0, 4);
		DELAY(10000);
	}
	if (1) {
		au_wr(au, 0, AU_REG_CODECST, 0x8068, 4);
		DELAY(10000);
		au_wr(au, 0, AU_REG_CODECST, 0x00e8, 4);
		DELAY(10000);
	} else {
		au_wr(au, 0, AU_REG_CODECST, 0x00a8, 4);
 		DELAY(100000);
		au_wr(au, 0, AU_REG_CODECST, 0x80a8, 4);
		DELAY(100000);
		au_wr(au, 0, AU_REG_CODECST, 0x80e8, 4);
		DELAY(100000);
		au_wr(au, 0, AU_REG_CODECST, 0x80a8, 4);
		DELAY(100000);
		au_wr(au, 0, AU_REG_CODECST, 0x00a8, 4);
		DELAY(100000);
		au_wr(au, 0, AU_REG_CODECST, 0x00e8, 4);
		DELAY(100000);
	}

	/* init */
	for (i=0; i<32; i++) {
		au_wr(au, 0, AU_REG_CODECCHN+(i<<2), 0, 4);
		DELAY(10000);
	}
	au_wr(au, 0, AU_REG_CODECST, 0xe8, 4);
	DELAY(10000);
	au_wr(au, 0, AU_REG_CODECEN, 0, 4);

	/* setup codec */
	i=j=0;
	while (j<100 && (i & AU_CDC_READY)==0) {
		i=au_rd(au, 0, AU_REG_CODECST, 4);
		DELAY(1000);
		j++;
	}
	if (j==100) device_printf(dev, "codec not ready, status 0x%x\n", i);

   	/* init adb */
	/*au->x5c=0;*/
	for (i=0; i<32;  i++) au->x[i]=i+0x67;
	for (i=0; i<128; i++) au->y[i]=0x7f;
	for (i=0; i<128; i++) au->z[i]=0x1f;
	au_wr(au, 0, AU_REG_ADB, 0, 4);
	for (i=0; i<124; i++) au_wr(au, 0, AU_REG_RTBASE+(i<<2), 0xffffffff, 4);

	/* test */
	i=au_rd(au, 0, 0x107c0, 4);
 	if (i!=0xdeadbeef) device_printf(dev, "dma check failed: 0x%x\n", i);

	/* install mixer */
	au_wr(au, 0, AU_REG_IRQGLOB,
	      au_rd(au, 0, AU_REG_IRQGLOB, 4) | AU_IRQ_ENABLE, 4);
	/* braindead but it's what the oss/linux driver does
	 * for (i=0; i<0x80000000; i++) au_wr(au, 0, i<<2, 0, 4);
	 */
	au->routes[0]=au->routes[1]=au->routes[2]=au->routes[3]=0;
	/*au->x1e4=0;*/

	/* attach channel */
	au_addroute(au, 0x11, 0x48, 0x02);
	au_addroute(au, 0x11, 0x49, 0x03);
	au_encodec(au, 0);
	au_encodec(au, 1);

	for (i=0; i<48; i++) au_wr(au, 0, 0xf800+(i<<2), 0x20, 4);
	for (i=2; i<6; i++) au_wr(au, 0, 0xf800+(i<<2), 0, 4);
	au_wr(au, 0, 0xf8c0, 0x0843, 4);
	for (i=0; i<4; i++) au_clrfifo(au, i);

	return (0);
}