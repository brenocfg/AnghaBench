#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct source {int dummy; } ;
struct TYPE_4__ {int extended_regs; int reg_array_size; int readstack_sz; int obase; int ibase; int /*<<< orphan*/ * readstack; int /*<<< orphan*/ * reg; int /*<<< orphan*/  stack; } ;
struct TYPE_3__ {size_t ch; int /*<<< orphan*/  f; } ;

/* Variables and functions */
 unsigned int JUMP_TABLE_DATA_SIZE ; 
 int READSTACK_SIZE ; 
 int REG_ARRAY_SIZE_BIG ; 
 int REG_ARRAY_SIZE_SMALL ; 
 unsigned int UCHAR_MAX ; 
 TYPE_2__ bmachine ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jump_table ; 
 TYPE_1__* jump_table_data ; 
 int /*<<< orphan*/  stack_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unknown ; 

void
init_bmachine(bool extended_registers)
{
	unsigned int i;

	bmachine.extended_regs = extended_registers;
	bmachine.reg_array_size = bmachine.extended_regs ?
	    REG_ARRAY_SIZE_BIG : REG_ARRAY_SIZE_SMALL;

	bmachine.reg = calloc(bmachine.reg_array_size,
	    sizeof(bmachine.reg[0]));
	if (bmachine.reg == NULL)
		err(1, NULL);

	for (i = 0; i < UCHAR_MAX; i++)
		jump_table[i] = unknown;
	for (i = 0; i < JUMP_TABLE_DATA_SIZE; i++)
		jump_table[jump_table_data[i].ch] = jump_table_data[i].f;

	stack_init(&bmachine.stack);

	for (i = 0; i < bmachine.reg_array_size; i++)
		stack_init(&bmachine.reg[i]);

	bmachine.readstack_sz = READSTACK_SIZE;
	bmachine.readstack = calloc(sizeof(struct source),
	    bmachine.readstack_sz);
	if (bmachine.readstack == NULL)
		err(1, NULL);
	bmachine.obase = bmachine.ibase = 10;
}