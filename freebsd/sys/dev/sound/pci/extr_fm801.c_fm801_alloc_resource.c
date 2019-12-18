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
typedef  int /*<<< orphan*/  u_int ;
struct resource {int dummy; } ;
struct fm801_info {struct resource* reg; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int SYS_RES_IOPORT ; 
 struct fm801_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct resource *
fm801_alloc_resource(device_t bus, device_t child, int type, int *rid,
		     rman_res_t start, rman_res_t end, rman_res_t count,
		     u_int flags)
{
	struct fm801_info *fm801;

	fm801 = pcm_getdevinfo(bus);

	if (type == SYS_RES_IOPORT && *rid == PCIR_BAR(0))
		return (fm801->reg);

	return (NULL);
}