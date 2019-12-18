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
struct interface_info {int ufdesc; int /*<<< orphan*/  wfdesc; } ;
struct bpf_version {scalar_t__ bv_major; scalar_t__ bv_minor; TYPE_1__* bf_insns; int /*<<< orphan*/  bf_len; } ;
struct bpf_program {scalar_t__ bv_major; scalar_t__ bv_minor; TYPE_1__* bf_insns; int /*<<< orphan*/  bf_len; } ;
typedef  int /*<<< orphan*/  on ;
typedef  int /*<<< orphan*/  cap_rights_t ;
struct TYPE_2__ {int k; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  BIOCLOCK ; 
 int /*<<< orphan*/  BIOCSETWF ; 
 int /*<<< orphan*/  BIOCVERSION ; 
 scalar_t__ BPF_MAJOR_VERSION ; 
 scalar_t__ BPF_MINOR_VERSION ; 
 int /*<<< orphan*/  CAP_WRITE ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  IP_HDRINCL ; 
 int IP_MF ; 
 int IP_OFFMASK ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ caph_rights_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* dhcp_bpf_wfilter ; 
 int /*<<< orphan*/  dhcp_bpf_wfilter_len ; 
 int /*<<< orphan*/  error (char*) ; 
 int htons (int) ; 
 int /*<<< orphan*/  if_register_bpf (struct interface_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bpf_version*) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
if_register_send(struct interface_info *info)
{
	cap_rights_t rights;
	struct bpf_version v;
	struct bpf_program p;
	int sock, on = 1;

	/* Open a BPF device and hang it on this interface... */
	info->wfdesc = if_register_bpf(info, O_WRONLY);

	/* Make sure the BPF version is in range... */
	if (ioctl(info->wfdesc, BIOCVERSION, &v) < 0)
		error("Can't get BPF version: %m");

	if (v.bv_major != BPF_MAJOR_VERSION ||
	    v.bv_minor < BPF_MINOR_VERSION)
		error("Kernel BPF version out of range - recompile dhcpd!");

	/* Set up the bpf write filter program structure. */
	p.bf_len = dhcp_bpf_wfilter_len;
	p.bf_insns = dhcp_bpf_wfilter;

	if (dhcp_bpf_wfilter[7].k == 0x1fff)
		dhcp_bpf_wfilter[7].k = htons(IP_MF|IP_OFFMASK);

	if (ioctl(info->wfdesc, BIOCSETWF, &p) < 0)
		error("Can't install write filter program: %m");

	if (ioctl(info->wfdesc, BIOCLOCK, NULL) < 0)
		error("Cannot lock bpf");

	cap_rights_init(&rights, CAP_WRITE);
	if (caph_rights_limit(info->wfdesc, &rights) < 0)
		error("Can't limit bpf descriptor: %m");

	/*
	 * Use raw socket for unicast send.
	 */
	if ((sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) == -1)
		error("socket(SOCK_RAW): %m");
	if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &on,
	    sizeof(on)) == -1)
		error("setsockopt(IP_HDRINCL): %m");
	info->ufdesc = sock;
}