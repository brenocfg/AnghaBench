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
typedef  int qboolean ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ netadr_t ;

/* Variables and functions */
 int /*<<< orphan*/  NA_LOOPBACK ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

qboolean	NET_StringToAdr (char *s, netadr_t *a)
{	
	if (!strcmp (s, "localhost")) {
		memset (a, 0, sizeof(*a));
		a->type = NA_LOOPBACK;
		return true;
	}

	return false;
}