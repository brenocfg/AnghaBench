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
struct carp_softc {int dummy; } ;
typedef  int /*<<< orphan*/  md2 ;

/* Variables and functions */
 int /*<<< orphan*/  CARP_LOCK_ASSERT (struct carp_softc*) ; 
 int bcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  carp_hmac_generate (struct carp_softc*,int /*<<< orphan*/ *,unsigned char*) ; 

__attribute__((used)) static int
carp_hmac_verify(struct carp_softc *sc, uint32_t counter[2],
    unsigned char md[20])
{
	unsigned char md2[20];

	CARP_LOCK_ASSERT(sc);

	carp_hmac_generate(sc, counter, md2);

	return (bcmp(md, md2, sizeof(md2)));
}