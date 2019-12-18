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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int SLI4_EQCQ_CQ_ID_MASK_LO ; 

__attribute__((used)) static inline uint32_t sli_cq_doorbell(uint16_t n_popped, uint16_t id, uint8_t arm)
{
	uint32_t	reg = 0;
#if BYTE_ORDER == LITTLE_ENDIAN
	struct {
		uint32_t	cq_id_lo:10,
				qt:1,			/* queue type */
				cq_id_hi:5,
				number_popped:13,
				arm:1,
				:1,
				se:1;
	} * cq_doorbell = (void *)&reg;
#else
#error big endian version not defined
#endif

	cq_doorbell->cq_id_lo = id & SLI4_EQCQ_CQ_ID_MASK_LO;
	cq_doorbell->qt = 0;	/* CQ is type 0 (section 2.2.3.3 SLI Arch) */
	cq_doorbell->cq_id_hi = (id >> 10) & 0x1f;
	cq_doorbell->number_popped = n_popped;
	cq_doorbell->arm = arm;

	return reg;
}