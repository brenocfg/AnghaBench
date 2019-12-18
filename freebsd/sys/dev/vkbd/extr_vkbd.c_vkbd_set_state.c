#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vkbd_state_t ;
struct TYPE_3__ {int /*<<< orphan*/  kb_data; } ;
typedef  TYPE_1__ keyboard_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  bcopy (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
vkbd_set_state(keyboard_t *kbd, void *buf, size_t len)
{
	if (len < sizeof(vkbd_state_t))
		return (ENOMEM);
	bcopy(buf, kbd->kb_data, sizeof(vkbd_state_t)); /* XXX locking? */
	return (0);
}