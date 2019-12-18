#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ldns_rdf ;
struct TYPE_3__ {int /*<<< orphan*/ * _answerfrom; } ;
typedef  TYPE_1__ ldns_pkt ;

/* Variables and functions */

ldns_rdf *
ldns_pkt_answerfrom(const ldns_pkt *packet)
{
	return packet->_answerfrom;
}