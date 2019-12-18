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
typedef  int /*<<< orphan*/  uma_zone_t ;
struct mbuf {int flags; short type; } ;
struct mb_args {int flags; short type; } ;

/* Variables and functions */
 int MCLBYTES ; 
 struct mbuf* m_getcl (int,short,int) ; 
 int /*<<< orphan*/  m_getzone (int) ; 
 struct mbuf* uma_zalloc_arg (int /*<<< orphan*/ ,struct mbuf*,int) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  zone_mbuf ; 

struct mbuf *
m_getjcl(int how, short type, int flags, int size)
{
	struct mb_args args;
	struct mbuf *m, *n;
	uma_zone_t zone;

	if (size == MCLBYTES)
		return m_getcl(how, type, flags);

	args.flags = flags;
	args.type = type;

	m = uma_zalloc_arg(zone_mbuf, &args, how);
	if (m == NULL)
		return (NULL);

	zone = m_getzone(size);
	n = uma_zalloc_arg(zone, m, how);
	if (n == NULL) {
		uma_zfree(zone_mbuf, m);
		return (NULL);
	}
	return (m);
}