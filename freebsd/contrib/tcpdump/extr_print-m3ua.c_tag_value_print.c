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
typedef  int uint16_t ;
typedef  int const u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct m3ua_param_header {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
#define  M3UA_PARAM_CORR_ID 130 
#define  M3UA_PARAM_NETWORK_APPEARANCE 129 
#define  M3UA_PARAM_ROUTING_CTX 128 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int const) ; 
 int /*<<< orphan*/  istr ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
tag_value_print(netdissect_options *ndo,
                const u_char *buf, const uint16_t tag, const uint16_t size)
{
  switch (tag) {
  case M3UA_PARAM_NETWORK_APPEARANCE:
  case M3UA_PARAM_ROUTING_CTX:
  case M3UA_PARAM_CORR_ID:
    /* buf and size don't include the header */
    if (size < 4)
      goto invalid;
    ND_TCHECK2(*buf, size);
    ND_PRINT((ndo, "0x%08x", EXTRACT_32BITS(buf)));
    break;
  /* ... */
  default:
    ND_PRINT((ndo, "(length %u)", size + (u_int)sizeof(struct m3ua_param_header)));
    ND_TCHECK2(*buf, size);
  }
  return;

invalid:
  ND_PRINT((ndo, "%s", istr));
  ND_TCHECK2(*buf, size);
  return;
trunc:
  ND_PRINT((ndo, "%s", tstr));
}