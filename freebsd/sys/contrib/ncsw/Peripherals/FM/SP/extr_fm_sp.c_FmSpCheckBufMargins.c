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
struct TYPE_3__ {scalar_t__ startMargins; scalar_t__ endMargins; } ;
typedef  TYPE_1__ t_FmSpBufMargins ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  MAJOR ; 
 scalar_t__ MAX_EXT_BUFFER_OFFSET ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

t_Error FmSpCheckBufMargins(t_FmSpBufMargins *p_FmSpBufMargins)
{
    /* Check the margin definition */
    if (p_FmSpBufMargins->startMargins > MAX_EXT_BUFFER_OFFSET)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("bufMargins.startMargins can't be larger than %d", MAX_EXT_BUFFER_OFFSET));
    if (p_FmSpBufMargins->endMargins > MAX_EXT_BUFFER_OFFSET)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("bufMargins.endMargins can't be larger than %d", MAX_EXT_BUFFER_OFFSET));

    return E_OK;
}