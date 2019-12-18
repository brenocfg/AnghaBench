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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* LDNS_TRUST_ANCHOR_FILE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
usage(FILE *stream, const char *progname)
{
	fprintf(stream, "  Usage: %s name [@server] [type] [class]\n", progname);
	fprintf(stream, "\t<name>  can be a domain name or an IP address (-x lookups)\n");
	fprintf(stream, "\t<type>  defaults to A\n");
	fprintf(stream, "\t<class> defaults to IN\n");
	fprintf(stream, "\n\targuments may be placed in random order\n");
	fprintf(stream, "\n  Options:\n");
	fprintf(stream, "\t-D\t\tenable DNSSEC (DO bit)\n");
#ifdef HAVE_SSL
	fprintf(stream, "\t-T\t\ttrace from the root down to <name>\n");
	fprintf(stream, "\t-S\t\tchase signature(s) from <name> to a known key [*]\n");
#endif /*HAVE_SSL*/
	fprintf(stream, "\t-I <address>\tsource address to query from\n");
	fprintf(stream, "\t-V <number>\tverbosity (0-5)\n");
	fprintf(stream, "\t-Q\t\tquiet mode (overrules -V)\n");
	fprintf(stream, "\n");
	fprintf(stream, "\t-f file\t\tread packet from file and send it\n");
	fprintf(stream, "\t-i file\t\tread packet from file and print it\n");
	fprintf(stream, "\t-w file\t\twrite answer packet to file\n");
	fprintf(stream, "\t-q file\t\twrite query packet to file\n");
	fprintf(stream, "\t-h\t\tshow this help\n");
	fprintf(stream, "\t-v\t\tshow version\n");
	fprintf(stream, "\n  Query options:\n");
	fprintf(stream, "\t-4\t\tstay on ip4\n");
	fprintf(stream, "\t-6\t\tstay on ip6\n");
	fprintf(stream, "\t-a\t\tfallback to EDNS0 and TCP if the answer is truncated\n");
	fprintf(stream, "\t-b <bufsize>\tuse <bufsize> as the buffer size (defaults to 512 b)\n");
	fprintf(stream, "\t-c <file>\tuse file for rescursive nameserver configuration"
			"\n\t\t\t(/etc/resolv.conf)\n");
	fprintf(stream, "\t-k <file>\tspecify a file that contains a trusted DNSSEC key [**]\n");
	fprintf(stream, "\t\t\tUsed to verify any signatures in the current answer.\n");
	fprintf(stream, "\t\t\tWhen DNSSEC enabled tracing (-TD) or signature\n"
			"\t\t\tchasing (-S) and no key files are given, keys are read\n"
			"\t\t\tfrom: %s\n",
			LDNS_TRUST_ANCHOR_FILE);
	fprintf(stream, "\t-o <mnemonic>\tset flags to:"
			"\n\t\t\t[QR|qr][AA|aa][TC|tc][RD|rd][CD|cd][RA|ra][AD|ad]\n");
	fprintf(stream, "\t\t\tlowercase: unset bit, uppercase: set bit\n");
	fprintf(stream, "\t-p <port>\tuse <port> as remote port number\n");
	fprintf(stream, "\t-s\t\tshow the DS RR for each key in a packet\n");
	fprintf(stream, "\t-u\t\tsend the query with udp (the default)\n");
	fprintf(stream, "\t-x\t\tdo a reverse lookup\n");
	fprintf(stream, "\twhen doing a secure trace:\n");
	fprintf(stream, "\t-r <file>\tuse file as root servers hint file\n");
	fprintf(stream, "\t-t\t\tsend the query with tcp (connected)\n");
	fprintf(stream, "\t-d <domain>\tuse domain as the start point for the trace\n");
    fprintf(stream, "\t-y <name:key[:algo]>\tspecify named base64 tsig key, and optional an\n\t\t\talgorithm (defaults to hmac-md5.sig-alg.reg.int)\n");
	fprintf(stream, "\t-z\t\tdon't randomize the nameservers before use\n");
	fprintf(stream, "\n  [*] = enables/implies DNSSEC\n");
	fprintf(stream, "  [**] = can be given more than once\n");
	fprintf(stream, "\n  ldns-team@nlnetlabs.nl | http://www.nlnetlabs.nl/ldns/\n");
}