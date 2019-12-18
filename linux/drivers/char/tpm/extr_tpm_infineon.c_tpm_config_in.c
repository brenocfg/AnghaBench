#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ iotype; scalar_t__ index_off; scalar_t__ mem_base; scalar_t__ config_port; } ;

/* Variables and functions */
 scalar_t__ TPM_INF_IO_PORT ; 
 unsigned char inb (scalar_t__) ; 
 unsigned char readb (scalar_t__) ; 
 TYPE_1__ tpm_dev ; 

__attribute__((used)) static inline unsigned char tpm_config_in(unsigned char offset)
{
	if (tpm_dev.iotype == TPM_INF_IO_PORT)
		return inb(tpm_dev.config_port + offset);
	else
		return readb(tpm_dev.mem_base + tpm_dev.index_off + offset);
}