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
typedef  int /*<<< orphan*/  uint64_t ;
struct ntb_softc {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ NTB_ATOM ; 
 scalar_t__ NTB_XEON ; 
 int /*<<< orphan*/  intel_ntb_reg_read (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint64_t
db_ioread(struct ntb_softc *ntb, uint64_t regoff)
{

	if (ntb->type == NTB_ATOM)
		return (intel_ntb_reg_read(8, regoff));

	KASSERT(ntb->type == NTB_XEON, ("bad ntb type"));

	return (intel_ntb_reg_read(2, regoff));
}