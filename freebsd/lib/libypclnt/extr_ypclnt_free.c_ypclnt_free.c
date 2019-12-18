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
struct TYPE_4__ {struct TYPE_4__* error; struct TYPE_4__* server; struct TYPE_4__* map; struct TYPE_4__* domain; } ;
typedef  TYPE_1__ ypclnt_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
ypclnt_free(ypclnt_t *ypclnt)
{
	if (ypclnt != NULL) {
		free(ypclnt->domain);
		free(ypclnt->map);
		free(ypclnt->server);
		free(ypclnt->error);
		free(ypclnt);
	}
}