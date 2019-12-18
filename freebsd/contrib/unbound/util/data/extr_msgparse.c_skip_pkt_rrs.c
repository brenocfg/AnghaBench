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
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  skip_pkt_rr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
skip_pkt_rrs(sldns_buffer* pkt, int num)
{
	int i;
	for(i=0; i<num; i++) {
		if(!skip_pkt_rr(pkt))
			return 0;
	}
	return 1;
}