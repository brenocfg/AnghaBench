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
typedef  union ieee754sp {int dummy; } ieee754sp ;
struct TYPE_2__ {int nan2008; } ;

/* Variables and functions */
 int SPMANT (union ieee754sp) ; 
 scalar_t__ SP_FBITS ; 
 int SP_MBIT (scalar_t__) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__ ieee754_csr ; 
 int /*<<< orphan*/  ieee754sp_isnan (union ieee754sp) ; 

__attribute__((used)) static inline int ieee754sp_issnan(union ieee754sp x)
{
	int qbit;

	assert(ieee754sp_isnan(x));
	qbit = (SPMANT(x) & SP_MBIT(SP_FBITS - 1)) == SP_MBIT(SP_FBITS - 1);
	return ieee754_csr.nan2008 ^ qbit;
}