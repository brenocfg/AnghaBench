#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  pc ;
typedef  int /*<<< orphan*/  ib_portid_t ;
struct TYPE_2__ {int /*<<< orphan*/  pma_query_failures; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBWARN (char*,char const*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ibd_timeout ; 
 int /*<<< orphan*/  ibmad_port ; 
 int /*<<< orphan*/  mad_decode_field (int /*<<< orphan*/ *,int,void*) ; 
 char* mad_field_name (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pma_query_via (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portid2str (int /*<<< orphan*/ *) ; 
 scalar_t__ snprintf (char*,size_t,char*,char*,int) ; 
 TYPE_1__ summary ; 

__attribute__((used)) static int query_and_dump(char *buf, size_t size, ib_portid_t * portid,
			  char *node_name, int portnum,
			  const char *attr_name, uint16_t attr_id,
			  int start_field, int end_field)
{
	uint8_t pc[1024];
	uint32_t val = 0;
	int i, n;

	memset(pc, 0, sizeof(pc));

	if (!pma_query_via(pc, portid, portnum, ibd_timeout, attr_id,
			   ibmad_port)) {
		IBWARN("%s query failed on %s, %s port %d", attr_name,
		       node_name, portid2str(portid), portnum);
		summary.pma_query_failures++;
		return 0;
	}

	for (n = 0, i = start_field; i < end_field; i++) {
		mad_decode_field(pc, i, (void *)&val);
		if (val)
			n += snprintf(buf + n, size - n, " [%s == %u]",
				      mad_field_name(i), val);
	}

	return n;
}