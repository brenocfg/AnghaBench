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

/* Variables and functions */
#define  SN_TO_GLOBAL 129 
#define  SN_TO_LOCAL 128 
 int /*<<< orphan*/  SctpAliasLog (char*,char,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
logsctperror(char* errormsg, uint32_t vtag, int error, int direction)
{
	char dir;
	switch (direction) {
	case SN_TO_LOCAL:
		dir = 'L';
		break;
	case SN_TO_GLOBAL:
		dir = 'G';
		break;
	default:
		dir = '*';
		break;
	}
	SctpAliasLog("->%c %s (vt=%u) %d\n", dir, errormsg, ntohl(vtag), error);
}