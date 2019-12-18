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
struct fw_ohci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI1394_Version ; 
 int /*<<< orphan*/  reg_read (struct fw_ohci const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void flush_writes(const struct fw_ohci *ohci)
{
	/* Do a dummy read to flush writes. */
	reg_read(ohci, OHCI1394_Version);
}