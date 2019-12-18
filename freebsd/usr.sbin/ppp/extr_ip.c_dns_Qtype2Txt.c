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
typedef  scalar_t__ u_short ;

/* Variables and functions */
 char const* HexStr (scalar_t__,char*,int) ; 

__attribute__((used)) static const char *
dns_Qtype2Txt(u_short qtype)
{
  static char failure[6];
  struct {
    u_short id;
    const char *txt;
  } qtxt[] = {
    /* rfc1035/rfc1700 */
    { 1, "A" }, { 2, "NS" }, { 3, "MD" }, { 4, "MF" }, { 5, "CNAME" },
    { 6, "SOA" }, { 7, "MB" }, { 8, "MG" }, { 9, "MR" }, { 10, "NULL" },
    { 11, "WKS" }, { 12, "PTR" }, { 13, "HINFO" }, { 14, "MINFO" },
    { 15, "MX" }, { 16, "TXT" }, { 17, "RP" }, { 18, "AFSDB" },
    { 19, "X25" }, { 20, "ISDN" }, { 21, "RT" }, { 22, "NSAP" },
    { 23, "NSAP-PTR" }, { 24, "SIG" }, { 25, "KEY" }, { 26, "PX" },
    { 27, "GPOS" }, { 28, "AAAA" }, { 252, "AXFR" }, { 253, "MAILB" },
    { 254, "MAILA" }, { 255, "*" }
  };
  unsigned f;

  for (f = 0; f < sizeof qtxt / sizeof *qtxt; f++)
    if (qtxt[f].id == qtype)
      return qtxt[f].txt;

  return HexStr(qtype, failure, sizeof failure);
}