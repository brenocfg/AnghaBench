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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  flowid; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_ASSERTPKTHDR (struct mbuf*) ; 
 int /*<<< orphan*/  M_HASHTYPE_GET (struct mbuf*) ; 
 int rss_hash2bucket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
rss_m2bucket(struct mbuf *m, uint32_t *bucket_id)
{

	M_ASSERTPKTHDR(m);

	return(rss_hash2bucket(m->m_pkthdr.flowid, M_HASHTYPE_GET(m),
	    bucket_id));
}