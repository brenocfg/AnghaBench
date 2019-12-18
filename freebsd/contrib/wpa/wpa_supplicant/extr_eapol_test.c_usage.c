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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void usage(void)
{
	printf("usage:\n"
	       "eapol_test [-enWSv] -c<conf> [-a<AS IP>] [-p<AS port>] "
	       "[-s<AS secret>]\\\n"
	       "           [-r<count>] [-t<timeout>] [-C<Connect-Info>] \\\n"
	       "           [-M<client MAC address>] [-o<server cert file] \\\n"
	       "           [-N<attr spec>] [-R<PC/SC reader>] "
	       "[-P<PC/SC PIN>] \\\n"
	       "           [-A<client IP>] [-i<ifname>] [-T<ctrl_iface>]\n"
	       "eapol_test scard\n"
	       "eapol_test sim <PIN> <num triplets> [debug]\n"
	       "\n");
	printf("options:\n"
	       "  -c<conf> = configuration file\n"
	       "  -a<AS IP> = IP address of the authentication server, "
	       "default 127.0.0.1\n"
	       "  -p<AS port> = UDP port of the authentication server, "
	       "default 1812\n"
	       "  -s<AS secret> = shared secret with the authentication "
	       "server, default 'radius'\n"
	       "  -A<client IP> = IP address of the client, default: select "
	       "automatically\n"
	       "  -r<count> = number of re-authentications\n"
	       "  -e = Request EAP-Key-Name\n"
	       "  -W = wait for a control interface monitor before starting\n"
	       "  -S = save configuration after authentication\n"
	       "  -n = no MPPE keys expected\n"
	       "  -v = show version\n"
	       "  -t<timeout> = sets timeout in seconds (default: 30 s)\n"
	       "  -C<Connect-Info> = RADIUS Connect-Info (default: "
	       "CONNECT 11Mbps 802.11b)\n"
	       "  -M<client MAC address> = Set own MAC address "
	       "(Calling-Station-Id,\n"
	       "                           default: 02:00:00:00:00:01)\n"
	       "  -o<server cert file> = Write received server certificate\n"
	       "                         chain to the specified file\n"
	       "  -N<attr spec> = send arbitrary attribute specified by:\n"
	       "                  attr_id:syntax:value or attr_id\n"
	       "                  attr_id - number id of the attribute\n"
	       "                  syntax - one of: s, d, x\n"
	       "                     s = string\n"
	       "                     d = integer\n"
	       "                     x = octet string\n"
	       "                  value - attribute value.\n"
	       "       When only attr_id is specified, NULL will be used as "
	       "value.\n"
	       "       Multiple attributes can be specified by using the "
	       "option several times.\n");
}