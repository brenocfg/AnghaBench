#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ ibnd_node_cache_t ;
typedef  int /*<<< orphan*/  ibnd_fabric_t ;
struct TYPE_16__ {int /*<<< orphan*/  from_node_guid; TYPE_3__* f_int; } ;
typedef  TYPE_2__ ibnd_fabric_cache_t ;
struct TYPE_18__ {int /*<<< orphan*/  from_node; } ;
struct TYPE_17__ {TYPE_5__ fabric; } ;
typedef  TYPE_3__ f_internal_t ;

/* Variables and functions */
 int /*<<< orphan*/  IBND_DEBUG (char*,...) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  _destroy_ibnd_fabric_cache (TYPE_2__*) ; 
 TYPE_1__* _find_node (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ _load_header_info (int,TYPE_2__*,unsigned int*,unsigned int*) ; 
 scalar_t__ _load_node (int,TYPE_2__*) ; 
 scalar_t__ _load_port (int,TYPE_2__*) ; 
 scalar_t__ _rebuild_nodes (TYPE_2__*) ; 
 scalar_t__ _rebuild_ports (TYPE_2__*) ; 
 TYPE_3__* allocate_fabric_internal () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ group_nodes (TYPE_5__*) ; 
 int /*<<< orphan*/  ibnd_destroy_fabric (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,char,int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

ibnd_fabric_t *ibnd_load_fabric(const char *file, unsigned int flags)
{
	unsigned int node_count = 0;
	unsigned int port_count = 0;
	ibnd_fabric_cache_t *fabric_cache = NULL;
	f_internal_t *f_int = NULL;
	ibnd_node_cache_t *node_cache = NULL;
	int fd = -1;
	unsigned int i;

	if (!file) {
		IBND_DEBUG("file parameter NULL\n");
		return NULL;
	}

	if ((fd = open(file, O_RDONLY)) < 0) {
		IBND_DEBUG("open: %s\n", strerror(errno));
		return NULL;
	}

	fabric_cache =
	    (ibnd_fabric_cache_t *) malloc(sizeof(ibnd_fabric_cache_t));
	if (!fabric_cache) {
		IBND_DEBUG("OOM: fabric_cache\n");
		goto cleanup;
	}
	memset(fabric_cache, '\0', sizeof(ibnd_fabric_cache_t));

	f_int = allocate_fabric_internal();
	if (!f_int) {
		IBND_DEBUG("OOM: fabric\n");
		goto cleanup;
	}

	fabric_cache->f_int = f_int;

	if (_load_header_info(fd, fabric_cache, &node_count, &port_count) < 0)
		goto cleanup;

	for (i = 0; i < node_count; i++) {
		if (_load_node(fd, fabric_cache) < 0)
			goto cleanup;
	}

	for (i = 0; i < port_count; i++) {
		if (_load_port(fd, fabric_cache) < 0)
			goto cleanup;
	}

	/* Special case - find from node */
	if (!(node_cache =
	      _find_node(fabric_cache, fabric_cache->from_node_guid))) {
		IBND_DEBUG("Cache invalid: cannot find from node\n");
		goto cleanup;
	}
	f_int->fabric.from_node = node_cache->node;

	if (_rebuild_nodes(fabric_cache) < 0)
		goto cleanup;

	if (_rebuild_ports(fabric_cache) < 0)
		goto cleanup;

	if (group_nodes(&f_int->fabric))
		goto cleanup;

	_destroy_ibnd_fabric_cache(fabric_cache);
	close(fd);
	return (ibnd_fabric_t *)&f_int->fabric;

cleanup:
	ibnd_destroy_fabric((ibnd_fabric_t *)f_int);
	_destroy_ibnd_fabric_cache(fabric_cache);
	close(fd);
	return NULL;
}