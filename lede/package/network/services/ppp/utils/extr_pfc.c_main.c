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
typedef  int /*<<< orphan*/  u_int32_t ;
struct bpf_program {int dummy; } ;
typedef  int /*<<< orphan*/  pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLT_PPP_PPPD ; 
 int /*<<< orphan*/  PPP_HDRLEN ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  bpf_dump (struct bpf_program*,int) ; 
 scalar_t__ pcap_compile (int /*<<< orphan*/ *,struct bpf_program*,char*,int,int /*<<< orphan*/ ) ; 
 char* pcap_geterr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pcap_open_dead (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int main (int argc, char ** argv)
{
    pcap_t  *pc; /* Fake struct pcap so we can compile expr */
    struct  bpf_program filter; /* Filter program for link-active pkts */
    u_int32_t netmask=0;

    int dflag = 3;
    if (argc == 4)
    {
	if (!strcmp (argv[1], "-d"))
	{
	    dflag = atoi (argv[2]);
	    argv += 2;
	    argc -=2;
	}
    }
    if (argc != 2)
    {
	printf ("usage; %s [ -d <debug_level> ] expression\n", argv[0]);
	return 1;
    }

    pc = pcap_open_dead(DLT_PPP_PPPD, PPP_HDRLEN);
    if (pcap_compile(pc, &filter, argv[1], 1, netmask) == 0)
    {
	printf ("#\n# Expression: %s\n#\n", argv[1]);
	bpf_dump (&filter, dflag);
	return 0;
    }
    else
    {
	printf("error in active-filter expression: %s\n", pcap_geterr(pc));
    }
    return 1;
}