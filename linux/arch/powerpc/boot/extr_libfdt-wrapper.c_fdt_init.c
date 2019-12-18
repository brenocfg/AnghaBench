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
struct TYPE_2__ {int /*<<< orphan*/  finalize; int /*<<< orphan*/  get_path; int /*<<< orphan*/  del_node; int /*<<< orphan*/  find_node_by_compatible; int /*<<< orphan*/  find_node_by_prop_value; int /*<<< orphan*/  create_node; int /*<<< orphan*/  get_parent; int /*<<< orphan*/  setprop; int /*<<< orphan*/  getprop; int /*<<< orphan*/  finddevice; } ;

/* Variables and functions */
 int EXPAND_GRANULARITY ; 
 void* buf ; 
 TYPE_1__ dt_ops ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 void* fdt ; 
 int fdt_open_into (void*,void*,int) ; 
 int /*<<< orphan*/  fdt_strerror (int) ; 
 int fdt_totalsize (void*) ; 
 int /*<<< orphan*/  fdt_wrapper_create_node ; 
 int /*<<< orphan*/  fdt_wrapper_del_node ; 
 int /*<<< orphan*/  fdt_wrapper_finalize ; 
 int /*<<< orphan*/  fdt_wrapper_find_node_by_compatible ; 
 int /*<<< orphan*/  fdt_wrapper_find_node_by_prop_value ; 
 int /*<<< orphan*/  fdt_wrapper_finddevice ; 
 int /*<<< orphan*/  fdt_wrapper_get_parent ; 
 int /*<<< orphan*/  fdt_wrapper_get_path ; 
 int /*<<< orphan*/  fdt_wrapper_getprop ; 
 int /*<<< orphan*/  fdt_wrapper_setprop ; 
 void* malloc (int) ; 

void fdt_init(void *blob)
{
	int err;
	int bufsize;

	dt_ops.finddevice = fdt_wrapper_finddevice;
	dt_ops.getprop = fdt_wrapper_getprop;
	dt_ops.setprop = fdt_wrapper_setprop;
	dt_ops.get_parent = fdt_wrapper_get_parent;
	dt_ops.create_node = fdt_wrapper_create_node;
	dt_ops.find_node_by_prop_value = fdt_wrapper_find_node_by_prop_value;
	dt_ops.find_node_by_compatible = fdt_wrapper_find_node_by_compatible;
	dt_ops.del_node = fdt_wrapper_del_node;
	dt_ops.get_path = fdt_wrapper_get_path;
	dt_ops.finalize = fdt_wrapper_finalize;

	/* Make sure the dt blob is the right version and so forth */
	fdt = blob;
	bufsize = fdt_totalsize(fdt) + EXPAND_GRANULARITY;
	buf = malloc(bufsize);
	if(!buf)
		fatal("malloc failed. can't relocate the device tree\n\r");

	err = fdt_open_into(fdt, buf, bufsize);

	if (err != 0)
		fatal("fdt_init(): %s\n\r", fdt_strerror(err));

	fdt = buf;
}