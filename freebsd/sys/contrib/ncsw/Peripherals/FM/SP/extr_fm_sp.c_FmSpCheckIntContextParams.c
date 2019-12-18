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
struct TYPE_3__ {int intContextOffset; scalar_t__ size; int extBufOffset; } ;
typedef  TYPE_1__ t_FmSpIntContextDataCopy ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  MAJOR ; 
 int MAX_EXT_OFFSET ; 
 scalar_t__ MAX_IC_SIZE ; 
 int MAX_INT_OFFSET ; 
 int OFFSET_UNITS ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

t_Error FmSpCheckIntContextParams(t_FmSpIntContextDataCopy *p_FmSpIntContextDataCopy)
{
    /* Check that divisible by 16 and not larger than 240 */
    if (p_FmSpIntContextDataCopy->intContextOffset >MAX_INT_OFFSET)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("intContext.intContextOffset can't be larger than %d", MAX_INT_OFFSET));
    if (p_FmSpIntContextDataCopy->intContextOffset % OFFSET_UNITS)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("intContext.intContextOffset has to be divisible by %d", OFFSET_UNITS));

    /* check that ic size+ic internal offset, does not exceed ic block size */
    if (p_FmSpIntContextDataCopy->size + p_FmSpIntContextDataCopy->intContextOffset > MAX_IC_SIZE)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("intContext.size + intContext.intContextOffset has to be smaller than %d", MAX_IC_SIZE));
    /* Check that divisible by 16 and not larger than 256 */
    if (p_FmSpIntContextDataCopy->size % OFFSET_UNITS)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("intContext.size  has to be divisible by %d", OFFSET_UNITS));

    /* Check that divisible by 16 and not larger than 4K */
    if (p_FmSpIntContextDataCopy->extBufOffset > MAX_EXT_OFFSET)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("intContext.extBufOffset can't be larger than %d", MAX_EXT_OFFSET));
    if (p_FmSpIntContextDataCopy->extBufOffset % OFFSET_UNITS)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("intContext.extBufOffset  has to be divisible by %d", OFFSET_UNITS));

    return E_OK;
}