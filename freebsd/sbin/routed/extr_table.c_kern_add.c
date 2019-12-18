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
struct khash {int /*<<< orphan*/  k_keep; int /*<<< orphan*/  k_state; void* k_mask; void* k_dst; } ;
typedef  void* naddr ;
struct TYPE_2__ {int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS_NEW ; 
 struct khash* kern_find (void*,void*,struct khash***) ; 
 int /*<<< orphan*/  memset (struct khash*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ now ; 
 scalar_t__ rtmalloc (int,char*) ; 

__attribute__((used)) static struct khash*
kern_add(naddr dst, naddr mask)
{
	struct khash *k, **pk;

	k = kern_find(dst, mask, &pk);
	if (k != NULL)
		return k;

	k = (struct khash *)rtmalloc(sizeof(*k), "kern_add");

	memset(k, 0, sizeof(*k));
	k->k_dst = dst;
	k->k_mask = mask;
	k->k_state = KS_NEW;
	k->k_keep = now.tv_sec;
	*pk = k;

	return k;
}