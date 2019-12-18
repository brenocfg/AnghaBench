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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 scalar_t__ LABEL_IS_PTR (scalar_t__) ; 
 int /*<<< orphan*/  PTR_OFFSET (scalar_t__,scalar_t__) ; 
 int dname_pkt_compare (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 scalar_t__* sldns_buffer_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smart_compare(sldns_buffer* pkt, uint8_t* dnow, 
	uint8_t* dprfirst, uint8_t* dprlast)
{
	if(LABEL_IS_PTR(*dnow)) {
		/* ptr points to a previous dname */
		uint8_t* p = sldns_buffer_at(pkt, PTR_OFFSET(dnow[0], dnow[1]));
		if( p == dprfirst || p == dprlast )
			return 0;
		/* prev dname is also a ptr, both ptrs are the same. */
		if(LABEL_IS_PTR(*dprlast) &&
			dprlast[0] == dnow[0] && dprlast[1] == dnow[1])
			return 0;
	}
	return dname_pkt_compare(pkt, dnow, dprlast);
}