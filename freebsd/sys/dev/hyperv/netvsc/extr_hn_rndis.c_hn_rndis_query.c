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
struct hn_softc {int dummy; } ;

/* Variables and functions */
 int hn_rndis_query2 (struct hn_softc*,int /*<<< orphan*/ ,void const*,size_t,void*,size_t*,size_t) ; 

__attribute__((used)) static int
hn_rndis_query(struct hn_softc *sc, uint32_t oid,
    const void *idata, size_t idlen, void *odata, size_t *odlen0)
{

	return (hn_rndis_query2(sc, oid, idata, idlen, odata, odlen0, *odlen0));
}