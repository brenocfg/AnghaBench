#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct pcap_rmtauth {int dummy; } ;
struct TYPE_13__ {int nocapture_local; } ;
struct TYPE_14__ {int /*<<< orphan*/  errbuf; TYPE_1__ opt; } ;
typedef  TYPE_2__ pcap_t ;

/* Variables and functions */
 int PCAP_BUF_SIZE ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int PCAP_ERROR_NO_SUCH_DEVICE ; 
 int PCAP_ERROR_PERM_DENIED ; 
 int PCAP_ERROR_PROMISC_PERM_DENIED ; 
 int PCAP_OPENFLAG_MAX_RESPONSIVENESS ; 
 int PCAP_OPENFLAG_NOCAPTURE_LOCAL ; 
 int PCAP_OPENFLAG_PROMISCUOUS ; 
#define  PCAP_SRC_FILE 130 
#define  PCAP_SRC_IFLOCAL 129 
#define  PCAP_SRC_IFREMOTE 128 
 int pcap_activate (TYPE_2__*) ; 
 int /*<<< orphan*/  pcap_close (TYPE_2__*) ; 
 TYPE_2__* pcap_create (char*,char*) ; 
 TYPE_2__* pcap_open_offline (char*,char*) ; 
 TYPE_2__* pcap_open_rpcap (char const*,int,int,int,struct pcap_rmtauth*,char*) ; 
 int pcap_parsesrcstr (char const*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int pcap_set_immediate_mode (TYPE_2__*,int) ; 
 int pcap_set_promisc (TYPE_2__*,int) ; 
 int pcap_set_snaplen (TYPE_2__*,int) ; 
 int pcap_set_timeout (TYPE_2__*,int) ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pcap_statustostr (int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

pcap_t *pcap_open(const char *source, int snaplen, int flags, int read_timeout, struct pcap_rmtauth *auth, char *errbuf)
{
	char name[PCAP_BUF_SIZE];
	int type;
	pcap_t *fp;
	int status;

	if (strlen(source) > PCAP_BUF_SIZE)
	{
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE, "The source string is too long. Cannot handle it correctly.");
		return NULL;
	}

	/*
	 * Determine the type of the source (file, local, remote) and,
	 * if it's file or local, the name of the file or capture device.
	 */
	if (pcap_parsesrcstr(source, &type, NULL, NULL, name, errbuf) == -1)
		return NULL;

	switch (type)
	{
	case PCAP_SRC_FILE:
		return pcap_open_offline(name, errbuf);

	case PCAP_SRC_IFLOCAL:
		fp = pcap_create(name, errbuf);
		break;

	case PCAP_SRC_IFREMOTE:
		/*
		 * Although we already have host, port and iface, we prefer
		 * to pass only 'source' to pcap_open_rpcap(), so that it
		 * has to call pcap_parsesrcstr() again.
		 * This is less optimized, but much clearer.
		 */
		return pcap_open_rpcap(source, snaplen, flags, read_timeout, auth, errbuf);

	default:
		strlcpy(errbuf, "Source type not supported", PCAP_ERRBUF_SIZE);
		return NULL;
	}

	if (fp == NULL)
		return (NULL);
	status = pcap_set_snaplen(fp, snaplen);
	if (status < 0)
		goto fail;
	if (flags & PCAP_OPENFLAG_PROMISCUOUS)
	{
		status = pcap_set_promisc(fp, 1);
		if (status < 0)
			goto fail;
	}
	if (flags & PCAP_OPENFLAG_MAX_RESPONSIVENESS)
	{
		status = pcap_set_immediate_mode(fp, 1);
		if (status < 0)
			goto fail;
	}
#ifdef _WIN32
	/*
	 * This flag is supported on Windows only.
	 * XXX - is there a way to support it with
	 * the capture mechanisms on UN*X?  It's not
	 * exactly a "set direction" operation; I
	 * think it means "do not capture packets
	 * injected with pcap_sendpacket() or
	 * pcap_inject()".
	 */
	/* disable loopback capture if requested */
	if (flags & PCAP_OPENFLAG_NOCAPTURE_LOCAL)
		fp->opt.nocapture_local = 1;
#endif /* _WIN32 */
	status = pcap_set_timeout(fp, read_timeout);
	if (status < 0)
		goto fail;
	status = pcap_activate(fp);
	if (status < 0)
		goto fail;
	return fp;

fail:
	if (status == PCAP_ERROR)
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE, "%s: %s",
		    name, fp->errbuf);
	else if (status == PCAP_ERROR_NO_SUCH_DEVICE ||
	    status == PCAP_ERROR_PERM_DENIED ||
	    status == PCAP_ERROR_PROMISC_PERM_DENIED)
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE, "%s: %s (%s)",
		    name, pcap_statustostr(status), fp->errbuf);
	else
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE, "%s: %s",
		    name, pcap_statustostr(status));
	pcap_close(fp);
	return NULL;
}