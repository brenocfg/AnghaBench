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
struct TYPE_2__ {int /*<<< orphan*/  flowid; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct inpcbinfo {int dummy; } ;
struct inpcbgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_HASHTYPE_GET (struct mbuf*) ; 
 struct inpcbgroup* in_pcbgroup_byhash (struct inpcbinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct inpcbgroup *
in_pcbgroup_bymbuf(struct inpcbinfo *pcbinfo, struct mbuf *m)
{

	return (in_pcbgroup_byhash(pcbinfo, M_HASHTYPE_GET(m),
	    m->m_pkthdr.flowid));
}