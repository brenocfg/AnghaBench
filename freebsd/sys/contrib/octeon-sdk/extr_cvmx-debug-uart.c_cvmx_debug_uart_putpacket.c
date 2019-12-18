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
 int /*<<< orphan*/  cvmx_debug_uart ; 
 int /*<<< orphan*/  cvmx_debug_uart_lock ; 
 int /*<<< orphan*/  cvmx_debug_uart_strhex (char*,unsigned char) ; 
 int /*<<< orphan*/  cvmx_spinlock_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_spinlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_uart_write_byte (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  cvmx_uart_write_string (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cvmx_debug_uart_putpacket(char *packet)
{
    size_t i;
    unsigned char csum;
    unsigned char *ptr = (unsigned char *) packet;
    char csumstr[3];

    for (csum = 0, i = 0; ptr[i]; i++)
      csum += ptr[i];
    cvmx_debug_uart_strhex(csumstr, csum);

    cvmx_spinlock_lock(&cvmx_debug_uart_lock);
    cvmx_uart_write_byte(cvmx_debug_uart, '$');
    cvmx_uart_write_string(cvmx_debug_uart, packet);
    cvmx_uart_write_byte(cvmx_debug_uart, '#');
    cvmx_uart_write_string(cvmx_debug_uart, csumstr);
    cvmx_spinlock_unlock(&cvmx_debug_uart_lock);

    return 0;
}