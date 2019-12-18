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
struct pcap_win {int /*<<< orphan*/  adapter; } ;
struct TYPE_3__ {int /*<<< orphan*/  errbuf; struct pcap_win* priv; } ;
typedef  TYPE_1__ pcap_t ;
typedef  int /*<<< orphan*/  bpf_u_int32 ;

/* Variables and functions */
 int oid_get_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcap_oid_get_request_npf(pcap_t *p, bpf_u_int32 oid, void *data, size_t *lenp)
{
	struct pcap_win *pw = p->priv;

	return (oid_get_request(pw->adapter, oid, data, lenp, p->errbuf));
}