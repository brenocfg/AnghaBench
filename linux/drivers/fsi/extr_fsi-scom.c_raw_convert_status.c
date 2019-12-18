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
typedef  int uint32_t ;
struct scom_access {int pib_status; int /*<<< orphan*/  intf_errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCOM_INTF_ERR_ABORT ; 
 int /*<<< orphan*/  SCOM_INTF_ERR_PARITY ; 
 int /*<<< orphan*/  SCOM_INTF_ERR_PROTECTION ; 
 int /*<<< orphan*/  SCOM_INTF_ERR_UNKNOWN ; 
 int SCOM_STATUS_ERR_SUMMARY ; 
 int SCOM_STATUS_PARITY ; 
 int SCOM_STATUS_PIB_ABORT ; 
 int SCOM_STATUS_PIB_RESP_MASK ; 
 int SCOM_STATUS_PIB_RESP_SHIFT ; 
 int SCOM_STATUS_PROTECTION ; 

__attribute__((used)) static void raw_convert_status(struct scom_access *acc, uint32_t status)
{
	acc->pib_status = (status & SCOM_STATUS_PIB_RESP_MASK) >>
		SCOM_STATUS_PIB_RESP_SHIFT;
	acc->intf_errors = 0;

	if (status & SCOM_STATUS_PROTECTION)
		acc->intf_errors |= SCOM_INTF_ERR_PROTECTION;
	else if (status & SCOM_STATUS_PARITY)
		acc->intf_errors |= SCOM_INTF_ERR_PARITY;
	else if (status & SCOM_STATUS_PIB_ABORT)
		acc->intf_errors |= SCOM_INTF_ERR_ABORT;
	else if (status & SCOM_STATUS_ERR_SUMMARY)
		acc->intf_errors |= SCOM_INTF_ERR_UNKNOWN;
}