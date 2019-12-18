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
typedef  int /*<<< orphan*/  Htop_Action ;

/* Variables and functions */
 int /*<<< orphan*/  Action_follow ; 
 size_t KEY_F (int) ; 
 size_t KEY_RECLICK ; 
 size_t KEY_RESIZE ; 
 int /*<<< orphan*/  actionCollapseIntoParent ; 
 int /*<<< orphan*/  actionExpandCollapseOrSortColumn ; 
 int /*<<< orphan*/  actionExpandOrCollapse ; 
 int /*<<< orphan*/  actionFilterByUser ; 
 int /*<<< orphan*/  actionHelp ; 
 int /*<<< orphan*/  actionHigherPriority ; 
 int /*<<< orphan*/  actionIncFilter ; 
 int /*<<< orphan*/  actionIncSearch ; 
 int /*<<< orphan*/  actionInvertSortOrder ; 
 int /*<<< orphan*/  actionKill ; 
 int /*<<< orphan*/  actionLowerPriority ; 
 int /*<<< orphan*/  actionLsof ; 
 int /*<<< orphan*/  actionQuit ; 
 int /*<<< orphan*/  actionRedraw ; 
 int /*<<< orphan*/  actionResize ; 
 int /*<<< orphan*/  actionSetAffinity ; 
 int /*<<< orphan*/  actionSetSortColumn ; 
 int /*<<< orphan*/  actionSetup ; 
 int /*<<< orphan*/  actionShowEnvScreen ; 
 int /*<<< orphan*/  actionSortByCPU ; 
 int /*<<< orphan*/  actionSortByMemory ; 
 int /*<<< orphan*/  actionSortByTime ; 
 int /*<<< orphan*/  actionStrace ; 
 int /*<<< orphan*/  actionTag ; 
 int /*<<< orphan*/  actionTagAllChildren ; 
 int /*<<< orphan*/  actionToggleKernelThreads ; 
 int /*<<< orphan*/  actionToggleProgramPath ; 
 int /*<<< orphan*/  actionToggleTreeView ; 
 int /*<<< orphan*/  actionToggleUserlandThreads ; 
 int /*<<< orphan*/  actionUntagAll ; 

void Action_setBindings(Htop_Action* keys) {
   keys[KEY_RESIZE] = actionResize;
   keys['M'] = actionSortByMemory;
   keys['T'] = actionSortByTime;
   keys['P'] = actionSortByCPU;
   keys['H'] = actionToggleUserlandThreads;
   keys['K'] = actionToggleKernelThreads;
   keys['p'] = actionToggleProgramPath;
   keys['t'] = actionToggleTreeView;
   keys[KEY_F(5)] = actionToggleTreeView;
   keys[KEY_F(4)] = actionIncFilter;
   keys['\\'] = actionIncFilter;
   keys[KEY_F(3)] = actionIncSearch;
   keys['/'] = actionIncSearch;

   keys[']'] = actionHigherPriority;
   keys[KEY_F(7)] = actionHigherPriority;
   keys['['] = actionLowerPriority;
   keys[KEY_F(8)] = actionLowerPriority;
   keys['I'] = actionInvertSortOrder;
   keys[KEY_F(6)] = actionExpandCollapseOrSortColumn;
   keys[KEY_F(18)] = actionExpandCollapseOrSortColumn;
   keys['<'] = actionSetSortColumn;
   keys[','] = actionSetSortColumn;
   keys['>'] = actionSetSortColumn;
   keys['.'] = actionSetSortColumn;
   keys[KEY_F(10)] = actionQuit;
   keys['q'] = actionQuit;
   keys['a'] = actionSetAffinity;
   keys[KEY_F(9)] = actionKill;
   keys['k'] = actionKill;
   keys[KEY_RECLICK] = actionExpandOrCollapse;
   keys['+'] = actionExpandOrCollapse;
   keys['='] = actionExpandOrCollapse;
   keys['-'] = actionExpandOrCollapse;
   keys['\177'] = actionCollapseIntoParent;
   keys['u'] = actionFilterByUser;
   keys['F'] = Action_follow;
   keys['S'] = actionSetup;
   keys['C'] = actionSetup;
   keys[KEY_F(2)] = actionSetup;
   keys['l'] = actionLsof;
   keys['s'] = actionStrace;
   keys[' '] = actionTag;
   keys['\014'] = actionRedraw; // Ctrl+L
   keys[KEY_F(1)] = actionHelp;
   keys['h'] = actionHelp;
   keys['?'] = actionHelp;
   keys['U'] = actionUntagAll;
   keys['c'] = actionTagAllChildren;
   keys['e'] = actionShowEnvScreen;
}