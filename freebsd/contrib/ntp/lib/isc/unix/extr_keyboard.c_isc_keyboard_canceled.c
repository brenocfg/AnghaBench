#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ result; } ;
typedef  TYPE_1__ isc_keyboard_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
 scalar_t__ ISC_R_CANCELED ; 
 int /*<<< orphan*/  ISC_TF (int) ; 

isc_boolean_t
isc_keyboard_canceled(isc_keyboard_t *keyboard) {
	return (ISC_TF(keyboard->result == ISC_R_CANCELED));
}