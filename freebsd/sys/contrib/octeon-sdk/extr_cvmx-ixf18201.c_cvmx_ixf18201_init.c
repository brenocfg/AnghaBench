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

/* Variables and functions */
 int /*<<< orphan*/  cvmx_ixf18201_mii_write (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cvmx_ixf18201_write16 (int,int) ; 
 int /*<<< orphan*/  cvmx_ixf18201_write32 (int,int) ; 
 int /*<<< orphan*/  cvmx_wait (int) ; 

int cvmx_ixf18201_init(void)
{
    int index;  /* For indexing the two 'ports' on ixf */
    int offset;

    /* Reset IXF, and take all blocks out of reset */

/*
Initializing...
PP0:~CONSOLE-> Changing register value, addr 0x0003, old: 0x0000, new: 0x0001
PP0:~CONSOLE-> Changing register value, addr 0x0003, old: 0x0001, new: 0x0000
PP0:~CONSOLE->  **** LLM201(Lochlomond) Driver loaded ****
PP0:~CONSOLE->  LLM201 Driver - Released on Tue Aug 28 09:51:30 2007.
PP0:~CONSOLE-> retval is: 0
PP0:~CONSOLE-> Changing register value, addr 0x0003, old: 0x0000, new: 0x0001
PP0:~CONSOLE-> Changing register value, addr 0x0003, old: 0x0001, new: 0x0000
PP0:~CONSOLE-> Brought all blocks out of reset
PP0:~CONSOLE-> Getting default config.
*/


    cvmx_ixf18201_write16(0x0003, 0x0001);
    cvmx_ixf18201_write16(0x0003, 0);

    /*
PP0:~CONSOLE-> Changing register value, addr 0x0000, old: 0x4014, new: 0x4010
PP0:~CONSOLE-> Changing register value, addr 0x0000, old: 0x4010, new: 0x4014
PP0:~CONSOLE-> Changing register value, addr 0x0004, old: 0x01ff, new: 0x0140
PP0:~CONSOLE-> Changing register value, addr 0x0009, old: 0x007f, new: 0x0000
    */
    cvmx_ixf18201_write16(0x0000, 0x4010);
    cvmx_ixf18201_write16(0x0000, 0x4014);
    cvmx_ixf18201_write16(0x0004, 0x0140);
    cvmx_ixf18201_write16(0x0009, 0);


    /*
PP0:~CONSOLE-> Changing register value, addr 0x000e, old: 0x0000, new: 0x000f
PP0:~CONSOLE-> Changing register value, addr 0x000f, old: 0x0000, new: 0x0004
PP0:~CONSOLE-> Changing register value, addr 0x000f, old: 0x0004, new: 0x0006
PP0:~CONSOLE-> Changing register value, addr 0x000e, old: 0x000f, new: 0x00f0
PP0:~CONSOLE-> Changing register value, addr 0x000f, old: 0x0006, new: 0x0040
PP0:~CONSOLE-> Changing register value, addr 0x000f, old: 0x0040, new: 0x0060
    */
    // skip GPIO, 0xe/0xf


    /*
PP0:~CONSOLE-> Changing register value, addr 0x3100, old: 0x57fb, new: 0x7f7b
PP0:~CONSOLE-> Changing register value, addr 0x3600, old: 0x57fb, new: 0x7f7b
PP0:~CONSOLE-> Changing register value, addr 0x3005, old: 0x8010, new: 0x0040
PP0:~CONSOLE-> Changing register value, addr 0x3006, old: 0x061a, new: 0x0000
PP0:~CONSOLE-> Changing register value, addr 0x3505, old: 0x8010, new: 0x0040
PP0:~CONSOLE-> Changing register value, addr 0x3506, old: 0x061a, new: 0x0000
    */
    for (index = 0; index < 2;index++ )
    {
        offset = 0x500 * index;
        cvmx_ixf18201_write32(0x3100 + offset, 0x47f7b);
        cvmx_ixf18201_write16(0x3005 + offset, 0x0040);
        cvmx_ixf18201_write16(0x3006 + offset, 0);
    }

    /*PP0:~CONSOLE->   *** SPI soft reset ***, block id: 0
PP0:~CONSOLE-> Changing register value, addr 0x3007, old: 0xf980, new: 0xf9c0
PP0:~CONSOLE-> Changing register value, addr 0x3008, old: 0xa6f0, new: 0x36f0
PP0:~CONSOLE-> Changing register value, addr 0x3000, old: 0x0080, new: 0x0060
PP0:~CONSOLE-> Changing register value, addr 0x3002, old: 0x0200, new: 0x0040
PP0:~CONSOLE-> Changing register value, addr 0x3003, old: 0x0100, new: 0x0000
PP0:~CONSOLE-> Changing register value, addr 0x30c2, old: 0x0080, new: 0x0060
PP0:~CONSOLE-> Changing register value, addr 0x300a, old: 0x0800, new: 0x0000
PP0:~CONSOLE-> Changing register value, addr 0x3007, old: 0xf9c0, new: 0x89c0
PP0:~CONSOLE-> Changing register value, addr 0x3016, old: 0x0000, new: 0x0010
PP0:~CONSOLE-> Changing register value, addr 0x3008, old: 0x36f0, new: 0x3610
PP0:~CONSOLE-> Changing register value, addr 0x3012, old: 0x0000, new: 0x0010
PP0:~CONSOLE-> Changing register value, addr 0x3007, old: 0x89c0, new: 0x8980
PP0:~CONSOLE-> Changing register value, addr 0x3008, old: 0x3610, new: 0xa210
PP0:~CONSOLE->

    */


    for (index = 0; index < 2;index++ )
    {
        offset = 0x500 * index;
        int cal_len_min_1 = 0;  /* Calendar length -1.  Must match number
                                ** of ports configured for interface.*/
        cvmx_ixf18201_write16(0x3007 + offset, 0x81c0 | (cal_len_min_1 << 11));
        cvmx_ixf18201_write16(0x3008 + offset, 0x3600 | (cal_len_min_1 << 4));
        cvmx_ixf18201_write16(0x3000 + offset, 0x0060);
        cvmx_ixf18201_write16(0x3002 + offset, 0x0040);
        cvmx_ixf18201_write16(0x3003 + offset, 0x0000);
        cvmx_ixf18201_write16(0x30c2 + offset, 0x0060);
        cvmx_ixf18201_write16(0x300a + offset, 0x0000);
        cvmx_ixf18201_write16(0x3007 + offset, 0x81c0 | (cal_len_min_1 << 11));
        cvmx_ixf18201_write16(0x3016 + offset, 0x0010);
        cvmx_ixf18201_write16(0x3008 + offset, 0x3600 | (cal_len_min_1 << 4));
        cvmx_ixf18201_write16(0x3012 + offset, 0x0010);
        cvmx_ixf18201_write16(0x3007 + offset, 0x8180 | (cal_len_min_1 << 11));
        cvmx_ixf18201_write16(0x3008 + offset, 0xa200 | (cal_len_min_1 << 4));

        cvmx_ixf18201_write16(0x3090 + offset, 0x0301);  /* Enable hairpin loopback */
    }



    /*
PP0:~CONSOLE-> Changing register value, addr 0x0004, old: 0x0140, new: 0x1fff
PP0:~CONSOLE-> Changing register value, addr 0x0009, old: 0x0000, new: 0x007f
PP0:~CONSOLE-> Changing register value, addr 0x310b, old: 0x0004, new: 0xffff
PP0:~CONSOLE-> Changing register value, addr 0x310a, old: 0x7f7b, new: 0xffff

    */

    cvmx_ixf18201_write16(0x0004, 0x1fff);
    cvmx_ixf18201_write16(0x0009, 0x007f);
#if 0
    /* MDI autoscan */
    cvmx_ixf18201_write16(0x310b, 0xffff);
    cvmx_ixf18201_write16(0x310a, 0xffff);
#endif


    /*
    *** 32 bit register, trace only captures part of it...
PP0:~CONSOLE-> Changing register value, addr 0x3100, old: 0x7f7b, new: 0x7f78
PP0:~CONSOLE-> Changing register value, addr 0x3600, old: 0x7f7b, new: 0x7f78
    */

    for (index = 0; index < 2;index++ )
    {
        offset = 0x500 * index;
        cvmx_ixf18201_write32(0x3100 + offset, 0x47f7c); /* Also enable jumbo frames */
        /* Set max packet size to 9600 bytes, max supported by IXF18201 */
        cvmx_ixf18201_write32(0x3114 + offset, 0x25800000);
    }


    cvmx_wait(100000000);

    /* Now reset the PCS blocks in the phy.  This seems to be required after
    ** bringing up the Cortina. */
    cvmx_ixf18201_mii_write(1, 3, 0, 0x8000);
    cvmx_ixf18201_mii_write(5, 3, 0, 0x8000);


    return 1;

}