#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct sflow_counter_record_t {int /*<<< orphan*/  length; int /*<<< orphan*/  format; } ;
struct TYPE_11__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 scalar_t__ EXTRACT_32BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (struct sflow_counter_record_t const) ; 
#define  SFLOW_COUNTER_BASEVG 133 
#define  SFLOW_COUNTER_ETHERNET 132 
#define  SFLOW_COUNTER_GENERIC 131 
#define  SFLOW_COUNTER_PROCESSOR 130 
#define  SFLOW_COUNTER_TOKEN_RING 129 
#define  SFLOW_COUNTER_VLAN 128 
 int /*<<< orphan*/  print_sflow_counter_basevg (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  print_sflow_counter_ethernet (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  print_sflow_counter_generic (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  print_sflow_counter_processor (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  print_sflow_counter_token_ring (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  print_sflow_counter_vlan (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  print_unknown_data (TYPE_1__*,int /*<<< orphan*/  const*,char*,scalar_t__) ; 
 int /*<<< orphan*/  sflow_counter_type_values ; 
 char* tok2str (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int
sflow_print_counter_records(netdissect_options *ndo,
                            const u_char *pointer, u_int len, u_int records)
{
    u_int nrecords;
    const u_char *tptr;
    u_int tlen;
    u_int counter_type;
    u_int counter_len;
    u_int enterprise;
    const struct sflow_counter_record_t *sflow_counter_record;

    nrecords = records;
    tptr = pointer;
    tlen = len;

    while (nrecords > 0) {
	/* do we have the "header?" */
	if (tlen < sizeof(struct sflow_counter_record_t))
	    return 1;
	sflow_counter_record = (const struct sflow_counter_record_t *)tptr;
	ND_TCHECK(*sflow_counter_record);

	enterprise = EXTRACT_32BITS(sflow_counter_record->format);
	counter_type = enterprise & 0x0FFF;
	enterprise = enterprise >> 20;
	counter_len  = EXTRACT_32BITS(sflow_counter_record->length);
	ND_PRINT((ndo, "\n\t    enterprise %u, %s (%u) length %u",
	       enterprise,
	       (enterprise == 0) ? tok2str(sflow_counter_type_values,"Unknown",counter_type) : "Unknown",
	       counter_type,
	       counter_len));

	tptr += sizeof(struct sflow_counter_record_t);
	tlen -= sizeof(struct sflow_counter_record_t);

	if (tlen < counter_len)
	    return 1;
	if (enterprise == 0) {
	    switch (counter_type) {
	    case SFLOW_COUNTER_GENERIC:
		if (print_sflow_counter_generic(ndo, tptr, tlen))
		    return 1;
		break;
	    case SFLOW_COUNTER_ETHERNET:
		if (print_sflow_counter_ethernet(ndo, tptr, tlen))
		    return 1;
		break;
	    case SFLOW_COUNTER_TOKEN_RING:
		if (print_sflow_counter_token_ring(ndo, tptr,tlen))
		    return 1;
		break;
	    case SFLOW_COUNTER_BASEVG:
		if (print_sflow_counter_basevg(ndo, tptr, tlen))
		    return 1;
		break;
	    case SFLOW_COUNTER_VLAN:
		if (print_sflow_counter_vlan(ndo, tptr, tlen))
		    return 1;
		break;
	    case SFLOW_COUNTER_PROCESSOR:
		if (print_sflow_counter_processor(ndo, tptr, tlen))
		    return 1;
		break;
	    default:
		if (ndo->ndo_vflag <= 1)
		    print_unknown_data(ndo, tptr, "\n\t\t", counter_len);
		break;
	    }
	}
	tptr += counter_len;
	tlen -= counter_len;
	nrecords--;

    }

    return 0;

trunc:
    return 1;
}