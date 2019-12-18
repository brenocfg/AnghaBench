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
typedef  int /*<<< orphan*/  u_int8_t ;
struct sc_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMPCI_REG_SBADDR ; 
 int /*<<< orphan*/  CMPCI_REG_SBDATA ; 
 int /*<<< orphan*/  cmi_wr (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cmimix_wr(struct sc_info *sc, u_int8_t port, u_int8_t val)
{
	cmi_wr(sc, CMPCI_REG_SBADDR, port, 1);
	cmi_wr(sc, CMPCI_REG_SBDATA, val, 1);
}