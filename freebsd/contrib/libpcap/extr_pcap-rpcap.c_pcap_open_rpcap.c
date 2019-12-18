#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint32 ;
struct rpcap_openreply {int /*<<< orphan*/  tzoff; int /*<<< orphan*/  linktype; } ;
struct rpcap_header {int /*<<< orphan*/  plen; } ;
struct pcap_rpcap {int rmt_flags; int rmt_clientside; int /*<<< orphan*/  rmt_sockctrl; int /*<<< orphan*/  protocol_version; } ;
struct pcap_rmtauth {int dummy; } ;
struct addrinfo {int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
struct activehosts {int /*<<< orphan*/  protocol_version; int /*<<< orphan*/  sockctrl; } ;
struct TYPE_6__ {char* device; int timeout; } ;
struct TYPE_7__ {int snapshot; int activated; int /*<<< orphan*/  cleanup_op; int /*<<< orphan*/  stats_ex_op; int /*<<< orphan*/  stats_op; int /*<<< orphan*/  setnonblock_op; int /*<<< orphan*/  getnonblock_op; int /*<<< orphan*/  setfilter_op; int /*<<< orphan*/  save_current_filter_op; int /*<<< orphan*/  read_op; void* tzoff; void* linktype; TYPE_1__ opt; struct pcap_rpcap* priv; } ;
typedef  TYPE_2__ pcap_t ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_SOCKET ; 
 int MAXIMUM_SNAPLEN ; 
 int PCAP_BUF_SIZE ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_SRC_IFREMOTE ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 char* RPCAP_DEFAULT_NETPORT ; 
 int /*<<< orphan*/  RPCAP_MSG_OPEN_REQ ; 
 int RPCAP_NETBUF_SIZE ; 
 int /*<<< orphan*/  SOCKBUF_BUFFERIZE ; 
 int /*<<< orphan*/  SOCKBUF_CHECKONLY ; 
 int /*<<< orphan*/  SOCKOPEN_CLIENT ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_cleanup_rpcap ; 
 int /*<<< orphan*/  pcap_close (TYPE_2__*) ; 
 TYPE_2__* pcap_create_common (char*,int) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pcap_getnonblock_rpcap ; 
 int pcap_parsesrcstr (char*,int*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  pcap_read_rpcap ; 
 int /*<<< orphan*/  pcap_save_current_filter_rpcap ; 
 int /*<<< orphan*/  pcap_setfilter_rpcap ; 
 int /*<<< orphan*/  pcap_setnonblock_rpcap ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pcap_stats_ex_rpcap ; 
 int /*<<< orphan*/  pcap_stats_rpcap ; 
 int /*<<< orphan*/  rpcap_createhdr (struct rpcap_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rpcap_discard (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int rpcap_doauth (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pcap_rmtauth*,char*) ; 
 int rpcap_process_msg_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rpcap_header*,char*) ; 
 int rpcap_recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 struct activehosts* rpcap_remoteact_getsock (char*,int*,char*) ; 
 scalar_t__ sock_bufferize (char*,int,char*,int*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sock_init (char*,int /*<<< orphan*/ ) ; 
 int sock_initaddress (char*,char*,struct addrinfo*,struct addrinfo**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_open (struct addrinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_send (int /*<<< orphan*/ ,char*,int,char*,int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 
 scalar_t__ strlen (char*) ; 

pcap_t *pcap_open_rpcap(const char *source, int snaplen, int flags, int read_timeout, struct pcap_rmtauth *auth, char *errbuf)
{
	pcap_t *fp;
	char *source_str;
	struct pcap_rpcap *pr;		/* structure used when doing a remote live capture */
	char host[PCAP_BUF_SIZE], ctrlport[PCAP_BUF_SIZE], iface[PCAP_BUF_SIZE];
	struct activehosts *activeconn;		/* active connection, if there is one */
	int error;				/* '1' if rpcap_remoteact_getsock returned an error */
	SOCKET sockctrl;
	uint8 protocol_version;			/* negotiated protocol version */
	int active;
	uint32 plen;
	char sendbuf[RPCAP_NETBUF_SIZE];	/* temporary buffer in which data to be sent is buffered */
	int sendbufidx = 0;			/* index which keeps the number of bytes currently buffered */
	int retval;				/* store the return value of the functions */

	/* RPCAP-related variables */
	struct rpcap_header header;		/* header of the RPCAP packet */
	struct rpcap_openreply openreply;	/* open reply message */

	fp = pcap_create_common(errbuf, sizeof (struct pcap_rpcap));
	if (fp == NULL)
	{
		return NULL;
	}
	source_str = strdup(source);
	if (source_str == NULL) {
		pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
		    errno, "malloc");
		return NULL;
	}

	/*
	 * Turn a negative snapshot value (invalid), a snapshot value of
	 * 0 (unspecified), or a value bigger than the normal maximum
	 * value, into the maximum allowed value.
	 *
	 * If some application really *needs* a bigger snapshot
	 * length, we should just increase MAXIMUM_SNAPLEN.
	 *
	 * XXX - should we leave this up to the remote server to
	 * do?
	 */
	if (snaplen <= 0 || snaplen > MAXIMUM_SNAPLEN)
		snaplen = MAXIMUM_SNAPLEN;

	fp->opt.device = source_str;
	fp->snapshot = snaplen;
	fp->opt.timeout = read_timeout;
	pr = fp->priv;
	pr->rmt_flags = flags;

	/*
	 * determine the type of the source (NULL, file, local, remote)
	 * You must have a valid source string even if we're in active mode, because otherwise
	 * the call to the following function will fail.
	 */
	if (pcap_parsesrcstr(fp->opt.device, &retval, host, ctrlport, iface, errbuf) == -1)
	{
		pcap_close(fp);
		return NULL;
	}

	if (retval != PCAP_SRC_IFREMOTE)
	{
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE, "This function is able to open only remote interfaces");
		pcap_close(fp);
		return NULL;
	}

	/*
	 * Warning: this call can be the first one called by the user.
	 * For this reason, we have to initialize the WinSock support.
	 */
	if (sock_init(errbuf, PCAP_ERRBUF_SIZE) == -1)
	{
		pcap_close(fp);
		return NULL;
	}

	/* Check for active mode */
	activeconn = rpcap_remoteact_getsock(host, &error, errbuf);
	if (activeconn != NULL)
	{
		sockctrl = activeconn->sockctrl;
		protocol_version = activeconn->protocol_version;
		active = 1;
	}
	else
	{
		struct addrinfo hints;			/* temp, needed to open a socket connection */
		struct addrinfo *addrinfo;		/* temp, needed to open a socket connection */

		if (error)
		{
			/*
			 * Call failed.
			 */
			pcap_close(fp);
			return NULL;
		}

		/*
		 * We're not in active mode; let's try to open a new
		 * control connection.
		 */
		memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = PF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;

		if (ctrlport[0] == 0)
		{
			/* the user chose not to specify the port */
			if (sock_initaddress(host, RPCAP_DEFAULT_NETPORT, &hints, &addrinfo, errbuf, PCAP_ERRBUF_SIZE) == -1)
			{
				pcap_close(fp);
				return NULL;
			}
		}
		else
		{
			if (sock_initaddress(host, ctrlport, &hints, &addrinfo, errbuf, PCAP_ERRBUF_SIZE) == -1)
			{
				pcap_close(fp);
				return NULL;
			}
		}

		if ((sockctrl = sock_open(addrinfo, SOCKOPEN_CLIENT, 0, errbuf, PCAP_ERRBUF_SIZE)) == INVALID_SOCKET)
		{
			freeaddrinfo(addrinfo);
			pcap_close(fp);
			return NULL;
		}

		/* addrinfo is no longer used */
		freeaddrinfo(addrinfo);

		if (rpcap_doauth(sockctrl, &protocol_version, auth, errbuf) == -1)
		{
			sock_close(sockctrl, NULL, 0);
			pcap_close(fp);
			return NULL;
		}
		active = 0;
	}

	/*
	 * Now it's time to start playing with the RPCAP protocol
	 * RPCAP open command: create the request message
	 */
	if (sock_bufferize(NULL, sizeof(struct rpcap_header), NULL,
		&sendbufidx, RPCAP_NETBUF_SIZE, SOCKBUF_CHECKONLY, errbuf, PCAP_ERRBUF_SIZE))
		goto error_nodiscard;

	rpcap_createhdr((struct rpcap_header *) sendbuf, protocol_version,
	    RPCAP_MSG_OPEN_REQ, 0, (uint32) strlen(iface));

	if (sock_bufferize(iface, (int) strlen(iface), sendbuf, &sendbufidx,
		RPCAP_NETBUF_SIZE, SOCKBUF_BUFFERIZE, errbuf, PCAP_ERRBUF_SIZE))
		goto error_nodiscard;

	if (sock_send(sockctrl, sendbuf, sendbufidx, errbuf,
	    PCAP_ERRBUF_SIZE) < 0)
		goto error_nodiscard;

	/* Receive and process the reply message header. */
	if (rpcap_process_msg_header(sockctrl, protocol_version,
	    RPCAP_MSG_OPEN_REQ, &header, errbuf) == -1)
		goto error_nodiscard;
	plen = header.plen;

	/* Read the reply body */
	if (rpcap_recv(sockctrl, (char *)&openreply,
	    sizeof(struct rpcap_openreply), &plen, errbuf) == -1)
		goto error;

	/* Discard the rest of the message, if there is any. */
	if (rpcap_discard(pr->rmt_sockctrl, plen, errbuf) == -1)
		goto error_nodiscard;

	/* Set proper fields into the pcap_t struct */
	fp->linktype = ntohl(openreply.linktype);
	fp->tzoff = ntohl(openreply.tzoff);
	pr->rmt_sockctrl = sockctrl;
	pr->protocol_version = protocol_version;
	pr->rmt_clientside = 1;

	/* This code is duplicated from the end of this function */
	fp->read_op = pcap_read_rpcap;
	fp->save_current_filter_op = pcap_save_current_filter_rpcap;
	fp->setfilter_op = pcap_setfilter_rpcap;
	fp->getnonblock_op = pcap_getnonblock_rpcap;
	fp->setnonblock_op = pcap_setnonblock_rpcap;
	fp->stats_op = pcap_stats_rpcap;
#ifdef _WIN32
	fp->stats_ex_op = pcap_stats_ex_rpcap;
#endif
	fp->cleanup_op = pcap_cleanup_rpcap;

	fp->activated = 1;
	return fp;

error:
	/*
	 * When the connection has been established, we have to close it. So, at the
	 * beginning of this function, if an error occur we return immediately with
	 * a return NULL; when the connection is established, we have to come here
	 * ('goto error;') in order to close everything properly.
	 */

	/*
	 * Discard the rest of the message.
	 * We already reported an error; if this gets an error, just
	 * drive on.
	 */
	(void)rpcap_discard(pr->rmt_sockctrl, plen, NULL);

error_nodiscard:
	if (!active)
		sock_close(sockctrl, NULL, 0);

	pcap_close(fp);
	return NULL;
}