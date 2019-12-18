#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* buf; } ;
typedef  scalar_t__ KEYCMD ;
typedef  TYPE_1__ CStr ;

/* Variables and functions */
 scalar_t__* CcAltMap ; 
 scalar_t__* CcKeyMap ; 
 int /*<<< orphan*/  DeleteXkey (TYPE_1__ const*) ; 
 scalar_t__ F_XKEY ; 

void
ClearXkey(KEYCMD *map, const CStr *in)
{
    unsigned char c = (unsigned char) *(in->buf);
    if ((map[c] == F_XKEY) &&
	((map == CcKeyMap && CcAltMap[c] != F_XKEY) ||
	 (map == CcAltMap && CcKeyMap[c] != F_XKEY)))
	(void) DeleteXkey(in);
}