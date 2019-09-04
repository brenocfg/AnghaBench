#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int dwSize; scalar_t__ th32ProcessID; } ;
typedef  TYPE_1__ PROCESSENTRY32 ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ Process32First (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ Process32Next (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int find_pid(DWORD pid, HANDLE hSnapshot, PROCESSENTRY32 *pe32)
{
	pe32->dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hSnapshot, pe32)) {
		do {
			if (pe32->th32ProcessID == pid)
				return 1;
		} while (Process32Next(hSnapshot, pe32));
	}
	return 0;
}