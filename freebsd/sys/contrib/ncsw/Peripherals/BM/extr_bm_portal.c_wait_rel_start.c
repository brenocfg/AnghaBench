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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  t_Error ;
typedef  int /*<<< orphan*/  t_BmPortal ;
struct bm_rcr_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_BUSY ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_Sleep (int) ; 
 struct bm_rcr_entry* try_rel_start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline__ t_Error wait_rel_start(t_BmPortal             *p_BmPortal,
                                         struct bm_rcr_entry    **rel,
                                         uint32_t               flags)
{
    int tries = 100;

    UNUSED(flags);
    do {
        *rel = try_rel_start(p_BmPortal);
        XX_Sleep(1);
    } while (!*rel && --tries);

    if (!(*rel))
        return ERROR_CODE(E_BUSY);

    return E_OK;
}