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
struct sflow_ethernet_frame_t {int /*<<< orphan*/  type; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (struct sflow_ethernet_frame_t const) ; 

__attribute__((used)) static int
print_sflow_ethernet_frame(netdissect_options *ndo,
                           const u_char *pointer, u_int len)
{
    const struct sflow_ethernet_frame_t *sflow_ethernet_frame;

    if (len < sizeof(struct sflow_ethernet_frame_t))
	return 1;

    sflow_ethernet_frame = (const struct sflow_ethernet_frame_t *)pointer;
    ND_TCHECK(*sflow_ethernet_frame);

    ND_PRINT((ndo, "\n\t      frame len %u, type %u",
	   EXTRACT_32BITS(sflow_ethernet_frame->length),
	   EXTRACT_32BITS(sflow_ethernet_frame->type)));

    return 0;

trunc:
    return 1;
}