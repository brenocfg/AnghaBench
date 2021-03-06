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
struct sflow_counter_sample_t {int /*<<< orphan*/  seqnum; int /*<<< orphan*/  records; int /*<<< orphan*/  typesource; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_32BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (struct sflow_counter_sample_t const) ; 
 int sflow_print_counter_records (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ; 

__attribute__((used)) static int
sflow_print_counter_sample(netdissect_options *ndo,
                           const u_char *pointer, u_int len)
{
    const struct sflow_counter_sample_t *sflow_counter_sample;
    u_int           nrecords;
    u_int           typesource;
    u_int           type;
    u_int           index;

    if (len < sizeof(struct sflow_counter_sample_t))
	return 1;

    sflow_counter_sample = (const struct sflow_counter_sample_t *)pointer;
    ND_TCHECK(*sflow_counter_sample);

    typesource = EXTRACT_32BITS(sflow_counter_sample->typesource);
    nrecords   = EXTRACT_32BITS(sflow_counter_sample->records);
    type = typesource >> 24;
    index = typesource & 0x0FFF;

    ND_PRINT((ndo, " seqnum %u, type %u, idx %u, records %u",
	   EXTRACT_32BITS(sflow_counter_sample->seqnum),
	   type,
	   index,
	   nrecords));

    return sflow_print_counter_records(ndo, pointer + sizeof(struct sflow_counter_sample_t),
				       len - sizeof(struct sflow_counter_sample_t),
				       nrecords);

trunc:
    return 1;
}