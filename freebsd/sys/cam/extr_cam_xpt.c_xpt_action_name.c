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
typedef  int uint32_t ;
struct kv {char const* name; int v; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 struct kv* map ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

const char *
xpt_action_name(uint32_t action) 
{
	static char buffer[32];	/* Only for unknown messages -- racy */
	struct kv *walker = map;

	while (walker->name != NULL) {
		if (walker->v == action)
			return (walker->name);
		walker++;
	}

	snprintf(buffer, sizeof(buffer), "%#x", action);
	return (buffer);
}