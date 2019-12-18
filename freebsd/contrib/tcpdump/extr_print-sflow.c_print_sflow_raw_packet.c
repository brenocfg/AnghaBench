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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct sflow_expanded_flow_raw_t {int /*<<< orphan*/  header_size; int /*<<< orphan*/  stripped_bytes; int /*<<< orphan*/  length; int /*<<< orphan*/  protocol; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (struct sflow_expanded_flow_raw_t const) ; 
 int /*<<< orphan*/  sflow_flow_raw_protocol_values ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
print_sflow_raw_packet(netdissect_options *ndo,
                       const u_char *pointer, u_int len)
{
    const struct sflow_expanded_flow_raw_t *sflow_flow_raw;

    if (len < sizeof(struct sflow_expanded_flow_raw_t))
	return 1;

    sflow_flow_raw = (const struct sflow_expanded_flow_raw_t *)pointer;
    ND_TCHECK(*sflow_flow_raw);
    ND_PRINT((ndo, "\n\t      protocol %s (%u), length %u, stripped bytes %u, header_size %u",
	   tok2str(sflow_flow_raw_protocol_values,"Unknown",EXTRACT_32BITS(sflow_flow_raw->protocol)),
	   EXTRACT_32BITS(sflow_flow_raw->protocol),
	   EXTRACT_32BITS(sflow_flow_raw->length),
	   EXTRACT_32BITS(sflow_flow_raw->stripped_bytes),
	   EXTRACT_32BITS(sflow_flow_raw->header_size)));

    /* QUESTION - should we attempt to print the raw header itself?
       assuming of course there is wnough data present to do so... */

    return 0;

trunc:
    return 1;
}