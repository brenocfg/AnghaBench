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
struct secpolicy {int dummy; } ;
struct ipsec_softc {struct secpolicy** sp; } ;
typedef  int sa_family_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int IPSEC_DIR_INBOUND ; 

__attribute__((used)) static struct secpolicy *
ipsec_getpolicy(struct ipsec_softc *sc, int dir, sa_family_t af)
{

	switch (af) {
#ifdef INET
	case AF_INET:
		return (sc->sp[(dir == IPSEC_DIR_INBOUND ? 0: 1)]);
#endif
#ifdef INET6
	case AF_INET6:
		return (sc->sp[(dir == IPSEC_DIR_INBOUND ? 0: 1)
#ifdef INET
			+ 2
#endif
		]);
#endif
	}
	return (NULL);
}