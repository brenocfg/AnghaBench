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
 char const* HexStr (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
protoname(unsigned proto)
{
  static const char * const cftypes[] = {
    /* Check out the latest ``Assigned numbers'' rfc (1700) */
    NULL,
    "MRU",		/* 1: Maximum-Receive-Unit */
    "ACCMAP",		/* 2: Async-Control-Character-Map */
    "AUTHPROTO",	/* 3: Authentication-Protocol */
    "QUALPROTO",	/* 4: Quality-Protocol */
    "MAGICNUM",		/* 5: Magic-Number */
    "RESERVED",		/* 6: RESERVED */
    "PROTOCOMP",	/* 7: Protocol-Field-Compression */
    "ACFCOMP",		/* 8: Address-and-Control-Field-Compression */
    "FCSALT",		/* 9: FCS-Alternatives */
    "SDP",		/* 10: Self-Describing-Pad */
    "NUMMODE",		/* 11: Numbered-Mode */
    "MULTIPROC",	/* 12: Multi-Link-Procedure */
    "CALLBACK",		/* 13: Callback */
    "CONTIME",		/* 14: Connect-Time */
    "COMPFRAME",	/* 15: Compound-Frames */
    "NDE",		/* 16: Nominal-Data-Encapsulation */
    "MRRU",		/* 17: Multilink-MRRU */
    "SHORTSEQ",		/* 18: Multilink-Short-Sequence-Number-Header */
    "ENDDISC",		/* 19: Multilink-Endpoint-Discriminator */
    "PROPRIETRY",	/* 20: Proprietary */
    "DCEID",		/* 21: DCE-Identifier */
    "MULTIPP",		/* 22: Multi-Link-Plus-Procedure */
    "LDBACP",		/* 23: Link Discriminator for BACP */
  };

  if (proto > sizeof cftypes / sizeof *cftypes || cftypes[proto] == NULL)
    return HexStr(proto, NULL, 0);

  return cftypes[proto];
}