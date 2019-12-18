#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcap_win {int /*<<< orphan*/  adapter; } ;
struct TYPE_3__ {int /*<<< orphan*/  errbuf; struct pcap_win* priv; } ;
typedef  TYPE_1__ pcap_t ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  PACKET_MODE_DUMP ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 scalar_t__ PacketSetDumpLimits (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ PacketSetDumpName (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ PacketSetMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
pcap_live_dump_npf(pcap_t *p, char *filename, int maxsize, int maxpacks)
{
	struct pcap_win *pw = p->priv;
	BOOLEAN res;

	/* Set the packet driver in dump mode */
	res = PacketSetMode(pw->adapter, PACKET_MODE_DUMP);
	if(res == FALSE){
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    "Error setting dump mode");
		return (-1);
	}

	/* Set the name of the dump file */
	res = PacketSetDumpName(pw->adapter, filename, (int)strlen(filename));
	if(res == FALSE){
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    "Error setting kernel dump file name");
		return (-1);
	}

	/* Set the limits of the dump file */
	res = PacketSetDumpLimits(pw->adapter, maxsize, maxpacks);
	if(res == FALSE) {
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    		"Error setting dump limit");
		return (-1);
	}

	return (0);
}