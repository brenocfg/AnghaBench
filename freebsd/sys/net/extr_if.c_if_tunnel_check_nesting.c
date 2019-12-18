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
typedef  int /*<<< orphan*/  uint32_t ;
struct mbuf {int dummy; } ;
struct m_tag {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 struct m_tag* m_tag_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct m_tag* m_tag_locate (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct m_tag*) ; 
 int /*<<< orphan*/  m_tag_prepend (struct mbuf*,struct m_tag*) ; 

int
if_tunnel_check_nesting(struct ifnet *ifp, struct mbuf *m, uint32_t cookie,
    int limit)
{
	struct m_tag *mtag;
	int count;

	count = 1;
	mtag = NULL;
	while ((mtag = m_tag_locate(m, cookie, 0, mtag)) != NULL) {
		if (*(struct ifnet **)(mtag + 1) == ifp) {
			log(LOG_NOTICE, "%s: loop detected\n", if_name(ifp));
			return (EIO);
		}
		count++;
	}
	if (count > limit) {
		log(LOG_NOTICE,
		    "%s: if_output recursively called too many times(%d)\n",
		    if_name(ifp), count);
		return (EIO);
	}
	mtag = m_tag_alloc(cookie, 0, sizeof(struct ifnet *), M_NOWAIT);
	if (mtag == NULL)
		return (ENOMEM);
	*(struct ifnet **)(mtag + 1) = ifp;
	m_tag_prepend(m, mtag);
	return (0);
}