#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int handle; int status; } ;
struct TYPE_10__ {int handle; } ;
struct TYPE_12__ {TYPE_2__ usocket; TYPE_1__ file; } ;
struct TYPE_13__ {scalar_t__ type; TYPE_3__ sources; } ;
typedef  TYPE_4__ isc_entropysource_t ;
struct TYPE_14__ {int /*<<< orphan*/  sources; } ;
typedef  TYPE_5__ isc_entropy_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ ENTROPY_SOURCETYPE_FILE ; 
 scalar_t__ ENTROPY_SOURCETYPE_USOCKET ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 TYPE_4__* ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 TYPE_4__* ISC_LIST_NEXT (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int ISC_MAX (int,int) ; 
#define  isc_usocketsource_connected 133 
#define  isc_usocketsource_connecting 132 
#define  isc_usocketsource_disconnected 131 
#define  isc_usocketsource_ndesired 130 
#define  isc_usocketsource_reading 129 
#define  isc_usocketsource_wrote 128 
 int /*<<< orphan*/  link ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
wait_for_sources(isc_entropy_t *ent) {
	isc_entropysource_t *source;
	int maxfd, fd;
	int cc;
	fd_set reads;
	fd_set writes;

	maxfd = -1;
	FD_ZERO(&reads);
	FD_ZERO(&writes);

	source = ISC_LIST_HEAD(ent->sources);
	while (source != NULL) {
		if (source->type == ENTROPY_SOURCETYPE_FILE) {
			fd = source->sources.file.handle;
			if (fd >= 0) {
				maxfd = ISC_MAX(maxfd, fd);
				FD_SET(fd, &reads);
			}
		}
		if (source->type == ENTROPY_SOURCETYPE_USOCKET) {
			fd = source->sources.usocket.handle;
			if (fd >= 0) {
				switch (source->sources.usocket.status) {
				case isc_usocketsource_disconnected:
					break;
				case isc_usocketsource_connecting:
				case isc_usocketsource_connected:
				case isc_usocketsource_ndesired:
					maxfd = ISC_MAX(maxfd, fd);
					FD_SET(fd, &writes);
					break;
				case isc_usocketsource_wrote:
				case isc_usocketsource_reading:
					maxfd = ISC_MAX(maxfd, fd);
					FD_SET(fd, &reads);
					break;
				}
			}
		}
		source = ISC_LIST_NEXT(source, link);
	}

	if (maxfd < 0)
		return (-1);

	cc = select(maxfd + 1, &reads, &writes, NULL, NULL);
	if (cc < 0)
		return (-1);

	return (cc);
}