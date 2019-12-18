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
 scalar_t__ CVMX_HELPER_DISABLE_SPI4000_BACKPRESSURE ; 
 int /*<<< orphan*/  __cvmx_spi4000_write (int,int,int) ; 

__attribute__((used)) static void __cvmx_spi4000_configure_mac(int interface)
{
    int port;
    // IXF1010 configuration
    // ---------------------
    //
    // Step 1: Apply soft reset to TxFIFO and MAC
    //         MAC soft reset register. address=0x505
    //         TxFIFO soft reset. address=0x620
    __cvmx_spi4000_write(interface, 0x0505, 0x3ff);  // reset all the MACs
    __cvmx_spi4000_write(interface, 0x0620, 0x3ff);  // reset the TX FIFOs

    //         Global address and Configuration Register. address=0x500
    //
    // Step 2: Apply soft reset to RxFIFO and SPI.
    __cvmx_spi4000_write(interface, 0x059e, 0x3ff);  // reset the RX FIFOs

    // Step 3a: Take the MAC out of softreset
    //          MAC soft reset register. address=0x505
    __cvmx_spi4000_write(interface, 0x0505, 0x0);    // reset all the MACs

    // Step 3b: De-assert port enables.
    //          Global address and Configuration Register. address=0x500
    __cvmx_spi4000_write(interface, 0x0500, 0x0);    // disable all ports

    // Step 4: Assert Clock mode change En.
    //         Clock and interface mode Change En. address=Serdes base + 0x14
    //         Serdes (Serializer/de-serializer). address=0x780
    //         [Can't find this one]

    for (port=0; port < 10; port++)
    {
        int port_offset = port << 7;

        // Step 5: Set MAC interface mode GMII speed.
        //         MAC interface mode and RGMII speed register.
        //             address=port_index+0x10
        //
        //         OUT port_index+0x10, 0x07     //RGMII 1000 Mbps operation.
        __cvmx_spi4000_write(interface, port_offset | 0x0010, 0x3);

        // Set the max packet size to 16383 bytes, including the CRC
        __cvmx_spi4000_write(interface, port_offset | 0x000f, 0x3fff);

        // Step 6: Change Interface to Copper mode
        //         Interface mode register. address=0x501
        //         [Can't find this]

        // Step 7: MAC configuration
        //         Station address configuration.
        //         Source MAC address low register. Source MAC address 31-0.
        //             address=port_index+0x00
        //         Source MAC address high register. Source MAC address 47-32.
        //             address=port_index+0x01
        //         where Port index is 0x0 to 0x5.
        //         This address is inserted in the source address filed when
        //         transmitting pause frames, and is also used to compare against
        //         unicast pause frames at the receiving side.
        //
        //         OUT port_index+0x00, source MAC address low.
        __cvmx_spi4000_write(interface, port_offset | 0x0000, 0x0000);
        //         OUT port_index+0x01, source MAC address high.
        __cvmx_spi4000_write(interface, port_offset | 0x0001, 0x0000);

        // Step 8: Set desired duplex mode
        //         Desired duplex register. address=port_index+0x02
        //         [Reserved]

        // Step 9: Other configuration.
        //         FC Enable Register.             address=port_index+0x12
        //         Discard Unknown Control Frame.  address=port_index+0x15
        //         Diverse config write register.  address=port_index+0x18
        //         RX Packet Filter register.      address=port_index+0x19
        //
        // Step 9a: Tx FD FC Enabled / Rx FD FC Enabled
        if (CVMX_HELPER_DISABLE_SPI4000_BACKPRESSURE)
            __cvmx_spi4000_write(interface, port_offset | 0x0012, 0);
        else
            __cvmx_spi4000_write(interface, port_offset | 0x0012, 0x7);

        // Step 9b: Discard unknown control frames
        __cvmx_spi4000_write(interface, port_offset | 0x0015, 0x1);

        // Step 9c: Enable auto-CRC and auto-padding
        __cvmx_spi4000_write(interface, port_offset | 0x0018, 0x11cd); //??

        // Step 9d: Drop bad CRC / Drop Pause / No DAF
        __cvmx_spi4000_write(interface, port_offset | 0x0019, 0x00);
    }

    // Step 9d: Drop frames
    __cvmx_spi4000_write(interface, 0x059f, 0x03ff);

    for (port=0; port < 10; port++)
    {
        // Step 9e: Set the TX FIFO marks
        __cvmx_spi4000_write(interface, port + 0x0600, 0x0900); // TXFIFO High watermark
        __cvmx_spi4000_write(interface, port + 0x060a, 0x0800); // TXFIFO Low watermark
        __cvmx_spi4000_write(interface, port + 0x0614, 0x0380); // TXFIFO threshold
    }

    // Step 12: De-assert RxFIFO and SPI Rx/Tx reset
    __cvmx_spi4000_write(interface, 0x059e, 0x0);    // reset the RX FIFOs

    // Step 13: De-assert TxFIFO and MAC reset
    __cvmx_spi4000_write(interface, 0x0620, 0x0);    // reset the TX FIFOs

    // Step 14: Assert port enable
    //          Global address and Configuration Register. address=0x500
    __cvmx_spi4000_write(interface, 0x0500, 0x03ff); // enable all ports

    // Step 15: Disable loopback
    //          [Can't find this one]
}