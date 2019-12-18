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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ lisp_hdr_flags ;

/* Variables and functions */
 scalar_t__ LISP_MAP_NOTIFY ; 
 int /*<<< orphan*/  LISP_MAP_NOTIFY_IBIT_MASK ; 
 scalar_t__ LISP_MAP_REGISTER ; 
 int /*<<< orphan*/  LISP_MAP_REGISTER_IBIT_MASK ; 

__attribute__((used)) static inline uint8_t is_xtr_data_present(uint8_t type, uint8_t lisp_hdr_flags)
{
	uint8_t xtr_present = 0;

	if (type == LISP_MAP_REGISTER)
		xtr_present = (lisp_hdr_flags) & LISP_MAP_REGISTER_IBIT_MASK;
	else if (type == LISP_MAP_NOTIFY)
		xtr_present = (lisp_hdr_flags) & LISP_MAP_NOTIFY_IBIT_MASK;

	return xtr_present;
}