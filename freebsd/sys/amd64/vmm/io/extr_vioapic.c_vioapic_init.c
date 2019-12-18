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
struct vm {int dummy; } ;
struct vioapic {TYPE_1__* rtbl; int /*<<< orphan*/  mtx; struct vm* vm; } ;
struct TYPE_2__ {int reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  M_VIOAPIC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int REDIR_ENTRIES ; 
 struct vioapic* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct vioapic *
vioapic_init(struct vm *vm)
{
	int i;
	struct vioapic *vioapic;

	vioapic = malloc(sizeof(struct vioapic), M_VIOAPIC, M_WAITOK | M_ZERO);

	vioapic->vm = vm;
	mtx_init(&vioapic->mtx, "vioapic lock", NULL, MTX_SPIN);

	/* Initialize all redirection entries to mask all interrupts */
	for (i = 0; i < REDIR_ENTRIES; i++)
		vioapic->rtbl[i].reg = 0x0001000000010000UL;

	return (vioapic);
}