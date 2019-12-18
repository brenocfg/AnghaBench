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
 int /*<<< orphan*/  CALL ; 
 int /*<<< orphan*/  CODEC_COMMAND ; 
 int /*<<< orphan*/  M3_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int m3_rd_1 (struct sc_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
m3_initcd(kobj_t kobj, void *devinfo)
{
	struct sc_info *sc = (struct sc_info *)devinfo;
	u_int32_t data;

	M3_DEBUG(CALL, ("m3_initcd\n"));

	/* init ac-link */

	data = m3_rd_1(sc, CODEC_COMMAND);
	return ((data & 0x1) ? 0 : 1);
}