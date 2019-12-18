#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int characterCount; TYPE_1__* characterList; } ;
struct TYPE_3__ {char const* base; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ Q_stricmp (char const*,int /*<<< orphan*/ ) ; 
 char* UI_OpponentLeaderHead () ; 
 TYPE_2__ uiInfo ; 

__attribute__((used)) static const char *UI_OpponentLeaderModel(void) {
	int i;
	const char *head = UI_OpponentLeaderHead();
	for (i = 0; i < uiInfo.characterCount; i++) {
		if (Q_stricmp(head, uiInfo.characterList[i].name) == 0) {
			return uiInfo.characterList[i].base;
		}
	}
	return "James";
}