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
 char const* NumStr (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
protoname(int proto)
{
  static struct {
    int id;
    const char *txt;
  } cftypes[] = {
    /* Check out the latest ``Assigned numbers'' rfc (rfc1700.txt) */
    { 1, "IPADDRS" },		/* IP-Addresses */	/* deprecated */
    { 2, "COMPPROTO" },		/* IP-Compression-Protocol */
    { 3, "IPADDR" },		/* IP-Address */
    { 129, "PRIDNS" },		/* 129: Primary DNS Server Address */
    { 130, "PRINBNS" },		/* 130: Primary NBNS Server Address */
    { 131, "SECDNS" },		/* 131: Secondary DNS Server Address */
    { 132, "SECNBNS" }		/* 132: Secondary NBNS Server Address */
  };
  unsigned f;

  for (f = 0; f < sizeof cftypes / sizeof *cftypes; f++)
    if (cftypes[f].id == proto)
      return cftypes[f].txt;

  return NumStr(proto, NULL, 0);
}