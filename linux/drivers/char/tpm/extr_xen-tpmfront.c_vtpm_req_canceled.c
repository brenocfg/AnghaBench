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
typedef  int u8 ;
struct tpm_chip {int dummy; } ;

/* Variables and functions */
 int VTPM_STATUS_CANCELED ; 

__attribute__((used)) static bool vtpm_req_canceled(struct tpm_chip *chip, u8 status)
{
	return status & VTPM_STATUS_CANCELED;
}