#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * data; scalar_t__ length; } ;
struct TYPE_6__ {TYPE_1__ keyvalue; } ;
struct TYPE_7__ {TYPE_2__ key; int /*<<< orphan*/ * salt; int /*<<< orphan*/ * mkvno; } ;
typedef  TYPE_3__ Key ;

/* Variables and functions */

void
_kadm5_init_keys (Key *keys, int len)
{
    int i;

    for (i = 0; i < len; ++i) {
	keys[i].mkvno               = NULL;
	keys[i].salt                = NULL;
	keys[i].key.keyvalue.length = 0;
	keys[i].key.keyvalue.data   = NULL;
    }
}