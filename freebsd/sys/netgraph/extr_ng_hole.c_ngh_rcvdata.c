#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;
typedef  TYPE_3__* hinfo_p ;
struct TYPE_7__ {scalar_t__ len; } ;
struct TYPE_9__ {TYPE_2__ m_pkthdr; } ;
struct TYPE_6__ {int /*<<< orphan*/  octets; int /*<<< orphan*/  frames; } ;
struct TYPE_8__ {TYPE_1__ stats; } ;

/* Variables and functions */
 TYPE_5__* NGI_M (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 TYPE_3__* NG_HOOK_PRIVATE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ngh_rcvdata(hook_p hook, item_p item)
{
	const hinfo_p hip = NG_HOOK_PRIVATE(hook);

	hip->stats.frames++;
	hip->stats.octets += NGI_M(item)->m_pkthdr.len;
	NG_FREE_ITEM(item);
	return 0;
}