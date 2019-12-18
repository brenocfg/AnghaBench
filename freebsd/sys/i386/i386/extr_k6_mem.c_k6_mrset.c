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
typedef  int u_int64_t ;
typedef  int u_int32_t ;
struct mem_range_softc {int mr_ndesc; struct mem_range_desc* mr_desc; } ;
struct mem_range_desc {int /*<<< orphan*/  mr_len; int /*<<< orphan*/  mr_base; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOENT ; 
 int ENOSPC ; 
 int EOPNOTSUPP ; 
#define  MEMRANGE_SET_REMOVE 129 
#define  MEMRANGE_SET_UPDATE 128 
 int /*<<< orphan*/  UWCCR ; 
 int /*<<< orphan*/  bzero (struct mem_range_desc*,int) ; 
 int /*<<< orphan*/  disable_intr () ; 
 int /*<<< orphan*/  enable_intr () ; 
 int k6_mrmake (struct mem_range_desc*,int*) ; 
 int rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wbinvd () ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
k6_mrset(struct mem_range_softc *sc, struct mem_range_desc *desc, int *arg)
{
	u_int64_t reg;
	u_int32_t mtrr;
	int error, d;

	switch (*arg) {
	case MEMRANGE_SET_UPDATE:
		error = k6_mrmake(desc, &mtrr);
		if (error)
			return (error);
		for (d = 0; d < sc->mr_ndesc; d++) {
			if (!sc->mr_desc[d].mr_len) {
				sc->mr_desc[d] = *desc;
				goto out;
			}
			if (sc->mr_desc[d].mr_base == desc->mr_base &&
			    sc->mr_desc[d].mr_len == desc->mr_len)
				return (EEXIST);
		}
		return (ENOSPC);
	case MEMRANGE_SET_REMOVE:
		mtrr = 0;
		for (d = 0; d < sc->mr_ndesc; d++)
			if (sc->mr_desc[d].mr_base == desc->mr_base &&
			    sc->mr_desc[d].mr_len == desc->mr_len) {
				bzero(&sc->mr_desc[d], sizeof(sc->mr_desc[d]));
				goto out;
			}
		return (ENOENT);
	default:
		return (EOPNOTSUPP);
	}
out:	
	disable_intr();
	wbinvd();
	reg = rdmsr(UWCCR);
	reg &= ~(0xffffffff << (32 * d));
	reg |= mtrr << (32 * d);
	wrmsr(UWCCR, reg);
	wbinvd();
	enable_intr();

	return (0);
}