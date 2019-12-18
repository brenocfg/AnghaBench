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

/* Variables and functions */
 int /*<<< orphan*/  BindArrowKeys () ; 
 int /*<<< orphan*/ * CcAltMap ; 
 int /*<<< orphan*/ * CcKeyMap ; 
 int /*<<< orphan*/ * CcViCmdMap ; 
 int /*<<< orphan*/ * CcViMap ; 
 int NT_NUM_KEYS ; 
 int /*<<< orphan*/  ResetArrowKeys () ; 
 int /*<<< orphan*/  ResetXmap () ; 
 int /*<<< orphan*/  STRvimode ; 
 int VImode ; 
 int /*<<< orphan*/  ed_InitMetaBindings () ; 
 int /*<<< orphan*/  ed_InitNLSMaps () ; 
 int /*<<< orphan*/  setNS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_wordchars () ; 

void
ed_InitVIMaps(void)
{
    int i;

    VImode = 1;
    setNS(STRvimode);
    update_wordchars();

    ResetXmap();
    for (i = 0; i < NT_NUM_KEYS; i++) {
	CcKeyMap[i] = CcViMap[i];
	CcAltMap[i] = CcViCmdMap[i];
    }
    ed_InitMetaBindings();
    ed_InitNLSMaps();
    ResetArrowKeys();
    BindArrowKeys();
}