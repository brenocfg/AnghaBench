#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
struct TYPE_8__ {struct TYPE_8__* htnext; } ;
typedef  TYPE_1__ ibnd_port_t ;
struct TYPE_9__ {struct TYPE_9__* next; } ;
typedef  TYPE_2__ ibnd_node_t ;
struct TYPE_10__ {TYPE_1__** portstbl; TYPE_2__* nodes; } ;
typedef  TYPE_3__ ibnd_fabric_t ;

/* Variables and functions */
 int HTSZ ; 
 unsigned int IBND_CACHE_FABRIC_FLAG_NO_OVERWRITE ; 
 int /*<<< orphan*/  IBND_DEBUG (char*,...) ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 scalar_t__ _cache_header_counts (int,unsigned int,unsigned int) ; 
 scalar_t__ _cache_header_info (int,TYPE_3__*) ; 
 scalar_t__ _cache_node (int,TYPE_2__*) ; 
 scalar_t__ _cache_port (int,TYPE_1__*) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  errno ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  stat (char const*,struct stat*) ; 
 char const* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ unlink (char const*) ; 

int ibnd_cache_fabric(ibnd_fabric_t * fabric, const char *file,
		      unsigned int flags)
{
	struct stat statbuf;
	ibnd_node_t *node = NULL;
	ibnd_node_t *node_next = NULL;
	unsigned int node_count = 0;
	ibnd_port_t *port = NULL;
	ibnd_port_t *port_next = NULL;
	unsigned int port_count = 0;
	int fd;
	int i;

	if (!fabric) {
		IBND_DEBUG("fabric parameter NULL\n");
		return -1;
	}

	if (!file) {
		IBND_DEBUG("file parameter NULL\n");
		return -1;
	}

	if (!(flags & IBND_CACHE_FABRIC_FLAG_NO_OVERWRITE)) {
		if (!stat(file, &statbuf)) {
			if (unlink(file) < 0) {
				IBND_DEBUG("error removing '%s': %s\n",
					   file, strerror(errno));
				return -1;
			}
		}
	}
	else {
		if (!stat(file, &statbuf)) {
			IBND_DEBUG("file '%s' already exists\n", file);
			return -1;
		}
	}

	if ((fd = open(file, O_CREAT | O_EXCL | O_WRONLY, 0644)) < 0) {
		IBND_DEBUG("open: %s\n", strerror(errno));
		return -1;
	}

	if (_cache_header_info(fd, fabric) < 0)
		goto cleanup;

	node = fabric->nodes;
	while (node) {
		node_next = node->next;

		if (_cache_node(fd, node) < 0)
			goto cleanup;

		node_count++;
		node = node_next;
	}

	for (i = 0; i < HTSZ; i++) {
		port = fabric->portstbl[i];
		while (port) {
			port_next = port->htnext;

			if (_cache_port(fd, port) < 0)
				goto cleanup;

			port_count++;
			port = port_next;
		}
	}

	if (_cache_header_counts(fd, node_count, port_count) < 0)
		goto cleanup;

	if (close(fd) < 0) {
		IBND_DEBUG("close: %s\n", strerror(errno));
		goto cleanup;
	}

	return 0;

cleanup:
	unlink(file);
	close(fd);
	return -1;
}