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
struct transport {scalar_t__ verbose; int family; int /*<<< orphan*/  url; struct git_transport_data* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  uploadpack; int /*<<< orphan*/  receivepack; } ;
struct git_transport_data {TYPE_1__ options; int /*<<< orphan*/  fd; scalar_t__ conn; } ;

/* Variables and functions */
 int CONNECT_IPV4 ; 
 int CONNECT_IPV6 ; 
 int CONNECT_VERBOSE ; 
#define  TRANSPORT_FAMILY_ALL 130 
#define  TRANSPORT_FAMILY_IPV4 129 
#define  TRANSPORT_FAMILY_IPV6 128 
 scalar_t__ git_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int connect_setup(struct transport *transport, int for_push)
{
	struct git_transport_data *data = transport->data;
	int flags = transport->verbose > 0 ? CONNECT_VERBOSE : 0;

	if (data->conn)
		return 0;

	switch (transport->family) {
	case TRANSPORT_FAMILY_ALL: break;
	case TRANSPORT_FAMILY_IPV4: flags |= CONNECT_IPV4; break;
	case TRANSPORT_FAMILY_IPV6: flags |= CONNECT_IPV6; break;
	}

	data->conn = git_connect(data->fd, transport->url,
				 for_push ? data->options.receivepack :
				 data->options.uploadpack,
				 flags);

	return 0;
}