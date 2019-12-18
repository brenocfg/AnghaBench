#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dmaaddr; int /*<<< orphan*/ * start; } ;
struct lanai_dev {TYPE_1__ service; int /*<<< orphan*/  pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int SERVICE_ENTRIES ; 
 int SSTUFF_SET_ADDR (int /*<<< orphan*/ ) ; 
 int SSTUFF_SET_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ServWrite_Reg ; 
 int /*<<< orphan*/  ServiceStuff_Reg ; 
 int /*<<< orphan*/  lanai_buf_allocate (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lanai_buf_size (TYPE_1__*) ; 
 int /*<<< orphan*/  lanai_buf_size_cardorder (TYPE_1__*) ; 
 int /*<<< orphan*/  reg_write (struct lanai_dev*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int service_buffer_allocate(struct lanai_dev *lanai)
{
	lanai_buf_allocate(&lanai->service, SERVICE_ENTRIES * 4, 8,
	    lanai->pci);
	if (unlikely(lanai->service.start == NULL))
		return -ENOMEM;
	DPRINTK("allocated service buffer at %p, size %zu(%d)\n",
	    lanai->service.start,
	    lanai_buf_size(&lanai->service),
	    lanai_buf_size_cardorder(&lanai->service));
	/* Clear ServWrite register to be safe */
	reg_write(lanai, 0, ServWrite_Reg);
	/* ServiceStuff register contains size and address of buffer */
	reg_write(lanai,
	    SSTUFF_SET_SIZE(lanai_buf_size_cardorder(&lanai->service)) |
	    SSTUFF_SET_ADDR(lanai->service.dmaaddr),
	    ServiceStuff_Reg);
	return 0;
}