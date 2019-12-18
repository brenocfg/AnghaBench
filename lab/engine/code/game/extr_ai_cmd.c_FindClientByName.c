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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int maxclients; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClientName (int,char*,int) ; 
 int MAX_INFO_STRING ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 TYPE_1__ level ; 
 scalar_t__ stristr (char*,char*) ; 

int FindClientByName(char *name) {
	int i;
	char buf[MAX_INFO_STRING];

	for (i = 0; i < level.maxclients; i++) {
		ClientName(i, buf, sizeof(buf));
		if (!Q_stricmp(buf, name)) return i;
	}
	for (i = 0; i < level.maxclients; i++) {
		ClientName(i, buf, sizeof(buf));
		if (stristr(buf, name)) return i;
	}
	return -1;
}