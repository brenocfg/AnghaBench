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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
struct pmf_function {char const* name; void** data; unsigned int length; int /*<<< orphan*/  link; void* phandle; void* flags; struct pmf_device* dev; void* driver_data; int /*<<< orphan*/  node; int /*<<< orphan*/  irq_clients; int /*<<< orphan*/  ref; } ;
struct pmf_device {int /*<<< orphan*/  functions; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pmf_function*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct pmf_function* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmf_get_device (struct pmf_device*) ; 
 scalar_t__ pmf_parse_one (struct pmf_function*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pmf_add_function_prop(struct pmf_device *dev, void *driverdata,
				 const char *name, u32 *data,
				 unsigned int length)
{
	int count = 0;
	struct pmf_function *func = NULL;

	DBG("pmf: Adding functions for platform-do-%s\n", name);

	while (length >= 12) {
		/* Allocate a structure */
		func = kzalloc(sizeof(*func), GFP_KERNEL);
		if (func == NULL)
			goto bail;
		kref_init(&func->ref);
		INIT_LIST_HEAD(&func->irq_clients);
		func->node = dev->node;
		func->driver_data = driverdata;
		func->name = name;
		func->phandle = data[0];
		func->flags = data[1];
		data += 2;
		length -= 8;
		func->data = data;
		func->length = length;
		func->dev = dev;
		DBG("pmf: idx %d: flags=%08x, phandle=%08x "
		    " %d bytes remaining, parsing...\n",
		    count+1, func->flags, func->phandle, length);
		if (pmf_parse_one(func, NULL, NULL, NULL)) {
			kfree(func);
			goto bail;
		}
		length -= func->length;
		data = (u32 *)(((u8 *)data) + func->length);
		list_add(&func->link, &dev->functions);
		pmf_get_device(dev);
		count++;
	}
 bail:
	DBG("pmf: Added %d functions\n", count);

	return count;
}