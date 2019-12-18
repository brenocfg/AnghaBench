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
typedef  scalar_t__ Char ;

/* Variables and functions */
 scalar_t__ AltKeyMap ; 
 int /*<<< orphan*/  CcAltMap ; 
 int /*<<< orphan*/  CcKeyMap ; 
 int /*<<< orphan*/  CurrentKeyMap ; 

__attribute__((used)) static void
c_alternativ_key_map(int state)
{
    switch (state) {
    case 0:
	CurrentKeyMap = CcKeyMap;
	break;
    case 1:
	CurrentKeyMap = CcAltMap;
	break;
    default:
	return;
    }

    AltKeyMap = (Char) state;
}