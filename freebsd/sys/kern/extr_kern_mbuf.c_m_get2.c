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
struct mbuf {int flags; short type; } ;
struct mb_args {int flags; short type; } ;

/* Variables and functions */
 int MCLBYTES ; 
 int MHLEN ; 
 int MJUMPAGESIZE ; 
 int MLEN ; 
 int M_PKTHDR ; 
 struct mbuf* uma_zalloc_arg (int /*<<< orphan*/ ,struct mbuf*,int) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  zone_jumbop ; 
 int /*<<< orphan*/  zone_mbuf ; 
 int /*<<< orphan*/  zone_pack ; 

struct mbuf *
m_get2(int size, int how, short type, int flags)
{
	struct mb_args args;
	struct mbuf *m, *n;

	args.flags = flags;
	args.type = type;

	if (size <= MHLEN || (size <= MLEN && (flags & M_PKTHDR) == 0))
		return (uma_zalloc_arg(zone_mbuf, &args, how));
	if (size <= MCLBYTES)
		return (uma_zalloc_arg(zone_pack, &args, how));

	if (size > MJUMPAGESIZE)
		return (NULL);

	m = uma_zalloc_arg(zone_mbuf, &args, how);
	if (m == NULL)
		return (NULL);

	n = uma_zalloc_arg(zone_jumbop, m, how);
	if (n == NULL) {
		uma_zfree(zone_mbuf, m);
		return (NULL);
	}

	return (m);
}