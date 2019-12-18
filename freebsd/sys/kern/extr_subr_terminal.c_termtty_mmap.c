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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_ooffset_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
struct tty {int dummy; } ;
struct terminal {TYPE_1__* tm_class; } ;
struct TYPE_2__ {int (* tc_mmap ) (struct terminal*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (struct terminal*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 struct terminal* tty_softc (struct tty*) ; 

__attribute__((used)) static int
termtty_mmap(struct tty *tp, vm_ooffset_t offset, vm_paddr_t * paddr,
    int nprot, vm_memattr_t *memattr)
{
	struct terminal *tm = tty_softc(tp);

	return (tm->tm_class->tc_mmap(tm, offset, paddr, nprot, memattr));
}