#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct in6_pktinfo {int dummy; } ;
typedef  int /*<<< orphan*/  isc_sockettype_t ;
typedef  scalar_t__ isc_result_t ;
struct TYPE_11__ {int /*<<< orphan*/  mctx; } ;
typedef  TYPE_2__ isc__socketmgr_t ;
struct TYPE_10__ {scalar_t__ impmagic; scalar_t__ magic; } ;
struct TYPE_12__ {int fd; int recvcmsgbuflen; int sendcmsgbuflen; struct TYPE_12__* sendcmsgbuf; struct TYPE_12__* recvcmsgbuf; TYPE_1__ common; int /*<<< orphan*/  writable_ev; int /*<<< orphan*/  readable_ev; int /*<<< orphan*/  lock; scalar_t__ bound; scalar_t__ connecting; scalar_t__ connected; scalar_t__ listener; scalar_t__ pending_accept; scalar_t__ pending_send; scalar_t__ pending_recv; int /*<<< orphan*/ * connect_ev; int /*<<< orphan*/  accept_list; int /*<<< orphan*/  send_list; int /*<<< orphan*/  recv_list; int /*<<< orphan*/ * tag; int /*<<< orphan*/  name; int /*<<< orphan*/ * statsindex; scalar_t__ dupped; int /*<<< orphan*/  type; TYPE_2__* manager; scalar_t__ references; } ;
typedef  TYPE_3__ isc__socket_t ;
typedef  int /*<<< orphan*/  intev_t ;
typedef  int ISC_SOCKADDR_LEN_T ;

/* Variables and functions */
 scalar_t__ ISCAPI_SOCKET_MAGIC ; 
 int /*<<< orphan*/  ISC_EVENTATTR_NOPURGE ; 
 int /*<<< orphan*/  ISC_EVENT_INIT (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISC_LINK_INIT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_LIST_INIT (int /*<<< orphan*/ ) ; 
 scalar_t__ ISC_R_NOMEMORY ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  ISC_SOCKEVENT_INTR ; 
 int /*<<< orphan*/  ISC_SOCKEVENT_INTW ; 
 scalar_t__ SOCKET_MAGIC ; 
 scalar_t__ cmsg_space (int) ; 
 void* isc_mem_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 scalar_t__ isc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static isc_result_t
allocate_socket(isc__socketmgr_t *manager, isc_sockettype_t type,
		isc__socket_t **socketp)
{
	isc__socket_t *sock;
	isc_result_t result;
	ISC_SOCKADDR_LEN_T cmsgbuflen;

	sock = isc_mem_get(manager->mctx, sizeof(*sock));

	if (sock == NULL)
		return (ISC_R_NOMEMORY);

	sock->common.magic = 0;
	sock->common.impmagic = 0;
	sock->references = 0;

	sock->manager = manager;
	sock->type = type;
	sock->fd = -1;
	sock->dupped = 0;
	sock->statsindex = NULL;

	ISC_LINK_INIT(sock, link);

	sock->recvcmsgbuf = NULL;
	sock->sendcmsgbuf = NULL;

	/*
	 * set up cmsg buffers
	 */
	cmsgbuflen = 0;
#if defined(USE_CMSG) && defined(ISC_PLATFORM_HAVEIN6PKTINFO)
	cmsgbuflen += cmsg_space(sizeof(struct in6_pktinfo));
#endif
#if defined(USE_CMSG) && defined(SO_TIMESTAMP)
	cmsgbuflen += cmsg_space(sizeof(struct timeval));
#endif
	sock->recvcmsgbuflen = cmsgbuflen;
	if (sock->recvcmsgbuflen != 0U) {
		sock->recvcmsgbuf = isc_mem_get(manager->mctx, cmsgbuflen);
		if (sock->recvcmsgbuf == NULL) {
			result = ISC_R_NOMEMORY;
			goto error;
		}
	}

	cmsgbuflen = 0;
#if defined(USE_CMSG) && defined(ISC_PLATFORM_HAVEIN6PKTINFO)
	cmsgbuflen += cmsg_space(sizeof(struct in6_pktinfo));
#if defined(IPV6_USE_MIN_MTU)
	/*
	 * Provide space for working around FreeBSD's broken IPV6_USE_MIN_MTU
	 * support.
	 */
	cmsgbuflen += cmsg_space(sizeof(int));
#endif
#endif
	sock->sendcmsgbuflen = cmsgbuflen;
	if (sock->sendcmsgbuflen != 0U) {
		sock->sendcmsgbuf = isc_mem_get(manager->mctx, cmsgbuflen);
		if (sock->sendcmsgbuf == NULL) {
			result = ISC_R_NOMEMORY;
			goto error;
		}
	}

	memset(sock->name, 0, sizeof(sock->name));
	sock->tag = NULL;

	/*
	 * set up list of readers and writers to be initially empty
	 */
	ISC_LIST_INIT(sock->recv_list);
	ISC_LIST_INIT(sock->send_list);
	ISC_LIST_INIT(sock->accept_list);
	sock->connect_ev = NULL;
	sock->pending_recv = 0;
	sock->pending_send = 0;
	sock->pending_accept = 0;
	sock->listener = 0;
	sock->connected = 0;
	sock->connecting = 0;
	sock->bound = 0;

	/*
	 * initialize the lock
	 */
	result = isc_mutex_init(&sock->lock);
	if (result != ISC_R_SUCCESS) {
		sock->common.magic = 0;
		sock->common.impmagic = 0;
		goto error;
	}

	/*
	 * Initialize readable and writable events
	 */
	ISC_EVENT_INIT(&sock->readable_ev, sizeof(intev_t),
		       ISC_EVENTATTR_NOPURGE, NULL, ISC_SOCKEVENT_INTR,
		       NULL, sock, sock, NULL, NULL);
	ISC_EVENT_INIT(&sock->writable_ev, sizeof(intev_t),
		       ISC_EVENTATTR_NOPURGE, NULL, ISC_SOCKEVENT_INTW,
		       NULL, sock, sock, NULL, NULL);

	sock->common.magic = ISCAPI_SOCKET_MAGIC;
	sock->common.impmagic = SOCKET_MAGIC;
	*socketp = sock;

	return (ISC_R_SUCCESS);

 error:
	if (sock->recvcmsgbuf != NULL)
		isc_mem_put(manager->mctx, sock->recvcmsgbuf,
			    sock->recvcmsgbuflen);
	if (sock->sendcmsgbuf != NULL)
		isc_mem_put(manager->mctx, sock->sendcmsgbuf,
			    sock->sendcmsgbuflen);
	isc_mem_put(manager->mctx, sock, sizeof(*sock));

	return (result);
}