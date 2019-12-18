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
struct ieee802_1x_mka_ki {scalar_t__ kn; int /*<<< orphan*/  mi; } ;

/* Variables and functions */
 int /*<<< orphan*/  MI_LEN ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_ki_equal(struct ieee802_1x_mka_ki *ki1,
		       struct ieee802_1x_mka_ki *ki2)
{
	return os_memcmp(ki1->mi, ki2->mi, MI_LEN) == 0 &&
		ki1->kn == ki2->kn;
}