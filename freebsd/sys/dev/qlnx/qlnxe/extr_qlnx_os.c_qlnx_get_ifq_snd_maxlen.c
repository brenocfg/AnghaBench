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
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int TX_RING_SIZE ; 

__attribute__((used)) static int
qlnx_get_ifq_snd_maxlen(qlnx_host_t *ha)
{
        return(TX_RING_SIZE - 1);
}