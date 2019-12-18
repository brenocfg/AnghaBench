#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int count; int /*<<< orphan*/ * list; } ;
struct TYPE_6__ {int count; int /*<<< orphan*/ * list; } ;
struct TYPE_5__ {scalar_t__ tags; } ;
typedef  TYPE_1__ NODE ;

/* Variables and functions */
 TYPE_4__ excludetags ; 
 TYPE_3__ includetags ; 
 scalar_t__ strstr (scalar_t__,int /*<<< orphan*/ ) ; 

int
matchtags(NODE *node)
{
	int	i;

	if (node->tags) {
		for (i = 0; i < excludetags.count; i++)
			if (strstr(node->tags, excludetags.list[i]))
				break;
		if (i < excludetags.count)
			return (0);

		for (i = 0; i < includetags.count; i++)
			if (strstr(node->tags, includetags.list[i]))
				break;
		if (i > 0 && i == includetags.count)
			return (0);
	} else if (includetags.count > 0) {
		return (0);
	}
	return (1);
}