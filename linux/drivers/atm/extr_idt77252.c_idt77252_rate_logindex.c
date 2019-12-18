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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct idt77252_dev {int dummy; } ;

/* Variables and functions */
 int idt77252_int_to_atmfp (int) ; 
 int /*<<< orphan*/ * rate_to_log ; 

__attribute__((used)) static u8
idt77252_rate_logindex(struct idt77252_dev *card, int pcr)
{
	u16 afp;

	afp = idt77252_int_to_atmfp(pcr < 0 ? -pcr : pcr);
	if (pcr < 0)
		return rate_to_log[(afp >> 5) & 0x1ff];
	return rate_to_log[((afp >> 5) + 1) & 0x1ff];
}