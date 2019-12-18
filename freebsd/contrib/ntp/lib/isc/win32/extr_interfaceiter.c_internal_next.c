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
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_3__ {scalar_t__ numIF; scalar_t__ v4IF; int /*<<< orphan*/ * pos4; int /*<<< orphan*/  IFData; int /*<<< orphan*/ * buf4; } ;
typedef  TYPE_1__ isc_interfaceiter_t ;
typedef  int /*<<< orphan*/  INTERFACE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_NOMORE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static isc_result_t
internal_next(isc_interfaceiter_t *iter) {
	if (iter->numIF >= iter->v4IF)
		return (ISC_R_NOMORE);

	/*
	 * The first one needs to be set up to point to the last
	 * Element of the array.  Go to the end and back up
	 * Microsoft's implementation is peculiar for returning
	 * the list in reverse order
	 */

	if (iter->numIF == 0)
		iter->pos4 = (INTERFACE_INFO *)(iter->buf4 + (iter->v4IF));

	iter->pos4--;
	if (&(iter->pos4) < &(iter->buf4))
		return (ISC_R_NOMORE);

	memset(&(iter->IFData), 0, sizeof(INTERFACE_INFO));
	memcpy(&(iter->IFData), iter->pos4, sizeof(INTERFACE_INFO));
	iter->numIF++;

	return (ISC_R_SUCCESS);
}