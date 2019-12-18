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
typedef  char u_short ;
typedef  char u_char ;
struct udphdr {char uh_ulen; } ;
struct dns_header {scalar_t__ opcode; scalar_t__ qr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogDNS ; 
 int /*<<< orphan*/  MAXHOSTNAMELEN ; 
 scalar_t__ OPCODE_QUERY ; 
 char* dns_Qclass2Txt (int /*<<< orphan*/ ) ; 
 char* dns_Qtype2Txt (int /*<<< orphan*/ ) ; 
 scalar_t__ log_IsKept (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char const*,char const*,char const*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  ntohs (char const) ; 

__attribute__((used)) static void
ip_LogDNS(const struct udphdr *uh, const char *direction)
{
  struct dns_header header;
  const u_short *pktptr;
  const u_char *ptr;
  u_short *hptr, tmp;
  unsigned len;

  ptr = (const char *)uh + sizeof *uh;
  len = ntohs(uh->uh_ulen) - sizeof *uh;
  if (len < sizeof header + 5)		/* rfc1024 */
    return;

  pktptr = (const u_short *)ptr;
  hptr = (u_short *)&header;
  ptr += sizeof header;
  len -= sizeof header;

  while (pktptr < (const u_short *)ptr) {
    *hptr++ = ntohs(*pktptr);		/* Careful of macro side-effects ! */
    pktptr++;
  }

  if (header.opcode == OPCODE_QUERY && header.qr == 0) {
    /* rfc1035 */
    char namewithdot[MAXHOSTNAMELEN + 1], *n;
    const char *qtype, *qclass;
    const u_char *end;

    n = namewithdot;
    end = ptr + len - 4;
    if (end - ptr >= (int)sizeof namewithdot)
      end = ptr + sizeof namewithdot - 1;
    while (ptr < end) {
      len = *ptr++;
      if ((int)len > end - ptr)
        len = end - ptr;
      if (n != namewithdot)
        *n++ = '.';
      memcpy(n, ptr, len);
      ptr += len;
      n += len;
    }
    *n = '\0';

    if (log_IsKept(LogDNS)) {
      memcpy(&tmp, end, sizeof tmp);
      qtype = dns_Qtype2Txt(ntohs(tmp));
      memcpy(&tmp, end + 2, sizeof tmp);
      qclass = dns_Qclass2Txt(ntohs(tmp));

      log_Printf(LogDNS, "%sbound query %s %s %s\n",
                 direction, qclass, qtype, namewithdot);
    }
  }
}