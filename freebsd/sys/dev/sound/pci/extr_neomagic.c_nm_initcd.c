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
typedef  int u_int32_t ;
struct sc_info {int dummy; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  nm_wr (struct sc_info*,int,int,int) ; 

__attribute__((used)) static u_int32_t
nm_initcd(kobj_t obj, void *devinfo)
{
	struct sc_info *sc = (struct sc_info *)devinfo;

	nm_wr(sc, 0x6c0, 0x01, 1);
#if 0
	/*
	 * The following code-line may cause a hang for some chipsets, see
	 * PR 56617.
	 * In case of a bugreport without this line have a look at the PR and
	 * conditionize the code-line based upon the specific version of
	 * the chip.
	 */
	nm_wr(sc, 0x6cc, 0x87, 1);
#endif
	nm_wr(sc, 0x6cc, 0x80, 1);
	nm_wr(sc, 0x6cc, 0x00, 1);
	return 1;
}