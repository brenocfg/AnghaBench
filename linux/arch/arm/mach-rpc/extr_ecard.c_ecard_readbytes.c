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
struct ecard_request {int address; int length; int use_loader; void* buffer; int /*<<< orphan*/ * ec; int /*<<< orphan*/  fn; } ;
typedef  int /*<<< orphan*/  ecard_t ;

/* Variables and functions */
 int /*<<< orphan*/  ecard_call (struct ecard_request*) ; 
 int /*<<< orphan*/  ecard_task_readbytes ; 

__attribute__((used)) static void
ecard_readbytes(void *addr, ecard_t *ec, int off, int len, int useld)
{
	struct ecard_request req;

	req.fn		= ecard_task_readbytes;
	req.ec		= ec;
	req.address	= off;
	req.length	= len;
	req.use_loader	= useld;
	req.buffer	= addr;

	ecard_call(&req);
}