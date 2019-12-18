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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/ * devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint8_t
devclass_create(devclass_t *dc_pp)
{
	if (dc_pp == NULL) {
		return (1);
	}
	if (dc_pp[0] == NULL) {
		dc_pp[0] = malloc(sizeof(**(dc_pp)),
		    M_DEVBUF, M_WAITOK | M_ZERO);

		if (dc_pp[0] == NULL) {
			return (1);
		}
	}
	return (0);
}