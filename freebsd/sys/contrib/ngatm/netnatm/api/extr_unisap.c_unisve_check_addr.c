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
struct unisve_addr {scalar_t__ tag; scalar_t__ type; scalar_t__ plan; int len; } ;

/* Variables and functions */
 scalar_t__ UNISVE_ABSENT ; 
 scalar_t__ UNISVE_ANY ; 
 int UNISVE_ERROR_ADDR_LEN ; 
 int UNISVE_ERROR_BAD_ADDR_TYPE ; 
 int UNISVE_ERROR_BAD_TAG ; 
 int UNISVE_ERROR_TYPE_PLAN_CONFLICT ; 
 int UNISVE_OK ; 
 scalar_t__ UNISVE_PRESENT ; 
 scalar_t__ UNI_ADDR_ATME ; 
 scalar_t__ UNI_ADDR_E164 ; 
 scalar_t__ UNI_ADDR_INTERNATIONAL ; 
 scalar_t__ UNI_ADDR_UNKNOWN ; 

int
unisve_check_addr(const struct unisve_addr *sve)
{
	if (sve->tag == UNISVE_ABSENT)
		return (UNISVE_OK);
	if (sve->tag == UNISVE_ANY)
		return (UNISVE_OK);
	if (sve->tag != UNISVE_PRESENT)
		return (UNISVE_ERROR_BAD_TAG);

	if (sve->type == UNI_ADDR_INTERNATIONAL) {
		if (sve->plan != UNI_ADDR_E164)
			return (UNISVE_ERROR_TYPE_PLAN_CONFLICT);
		if (sve->len == 0 || sve->len > 15)
			return (UNISVE_ERROR_ADDR_LEN);

	} else if (sve->type == UNI_ADDR_UNKNOWN) {
		if (sve->plan != UNI_ADDR_ATME)
			return (UNISVE_ERROR_TYPE_PLAN_CONFLICT);
		if (sve->len != 19)
			return (UNISVE_ERROR_ADDR_LEN);
	} else
		return (UNISVE_ERROR_BAD_ADDR_TYPE);

	return (UNISVE_OK);
}