#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int status; int speed; int duplex; } ;
struct TYPE_5__ {TYPE_1__ s; scalar_t__ u64; } ;
typedef  TYPE_2__ cvmx_gmxx_rxx_rx_inbnd_t ;

/* Variables and functions */
 int __cvmx_spi4000_mdio_read (int,int,int) ; 
 int /*<<< orphan*/  __cvmx_spi4000_write (int,int,int) ; 
 int /*<<< orphan*/ * interface_is_spi4000 ; 

cvmx_gmxx_rxx_rx_inbnd_t cvmx_spi4000_check_speed(int interface, int port)
{
    static int phy_status[10] = {0,};
    cvmx_gmxx_rxx_rx_inbnd_t link;
    int read_status;

    link.u64 = 0;

    if (!interface_is_spi4000[interface])
        return link;
    if (port>=10)
        return link;

    /* Register 0x11: PHY Specific Status Register
         Register   Function         Setting                     Mode   HW Rst SW Rst Notes
                                                                 RO     00     Retain note
         17.15:14   Speed            11 = Reserved
                                                                                      17.a
                                     10 = 1000 Mbps
                                     01 = 100 Mbps
                                     00 = 10 Mbps
         17.13      Duplex           1 = Full-duplex             RO     0      Retain note
                                     0 = Half-duplex                                  17.a
         17.12      Page Received    1 = Page received           RO, LH 0      0
                                     0 = Page not received
                                     1 = Resolved                RO     0      0      note
         17.11      Speed and
                                     0 = Not resolved                                 17.a
                    Duplex
                    Resolved
         17.10      Link (real time) 1 = Link up                 RO     0      0
                                     0 = Link down
                                                                 RO     000    000    note
                                     000 = < 50m
         17.9:7     Cable Length
                                     001 = 50 - 80m                                   17.b
                    (100/1000
                                     010 = 80 - 110m
                    modes only)
                                     011 = 110 - 140m
                                     100 = >140m
         17.6       MDI Crossover    1 = MDIX                    RO     0      0      note
                    Status           0 = MDI                                          17.a
         17.5       Downshift Sta-   1 = Downshift               RO     0      0
                    tus              0 = No Downshift
         17.4       Energy Detect    1 = Sleep                   RO     0      0
                    Status           0 = Active
         17.3       Transmit Pause   1 = Transmit pause enabled  RO     0      0      note17.
                    Enabled          0 = Transmit pause disabled                      a, 17.c
         17.2       Receive Pause    1 = Receive pause enabled   RO     0      0      note17.
                    Enabled          0 = Receive pause disabled                       a, 17.c
         17.1       Polarity (real   1 = Reversed                RO     0      0
                    time)            0 = Normal
         17.0       Jabber (real     1 = Jabber                  RO     0      Retain
                    time)            0 = No jabber
    */
    read_status = __cvmx_spi4000_mdio_read(interface, port, 0x11);
    if ((read_status & (1<<10)) == 0)
        read_status = 0; /* If the link is down, force zero */
    else
        read_status &= 0xe400; /* Strip off all the don't care bits */
    if (read_status != phy_status[port])
    {
        phy_status[port] = read_status;
        if (read_status & (1<<10))
        {
            /* If the link is up, we need to set the speed based on the PHY status */
            if (read_status & (1<<15))
                __cvmx_spi4000_write(interface, (port<<7) | 0x0010, 0x3); /* 1Gbps */
            else
                __cvmx_spi4000_write(interface, (port<<7) | 0x0010, 0x1); /* 100Mbps */
        }
        else
        {
            /* If the link is down, force 1Gbps so TX traffic dumps fast */
            __cvmx_spi4000_write(interface, (port<<7) | 0x0010, 0x3); /* 1Gbps */
        }
    }

    if (read_status & (1<<10))
    {
        link.s.status = 1; /* Link up */
        if (read_status & (1<<15))
            link.s.speed = 2;
        else
            link.s.speed = 1;
    }
    else
    {
        link.s.speed = 2; /* Use 1Gbps when down */
        link.s.status = 0; /* Link Down */
    }
    link.s.duplex = ((read_status & (1<<13)) != 0);

    return link;
}