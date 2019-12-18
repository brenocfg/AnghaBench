#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  baseAddr; } ;
typedef  TYPE_1__ t_FmMuram ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  IOMemSet32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT_TO_PTR (int /*<<< orphan*/ ) ; 

void FmMuramClear(t_Handle h_FmMuram)
{
    t_FmMuram   *p_FmMuram = ( t_FmMuram *)h_FmMuram;

    SANITY_CHECK_RETURN(h_FmMuram, E_INVALID_HANDLE);
    IOMemSet32(UINT_TO_PTR(p_FmMuram->baseAddr), 0, p_FmMuram->size);
}