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
struct sgx_softc {int enclave_size_max; } ;
struct secs_attr {scalar_t__ reserved1; scalar_t__ reserved2; scalar_t__ reserved3; int xfrm; int /*<<< orphan*/  mode64bit; scalar_t__* reserved4; } ;
struct secs {int size; int base; scalar_t__* reserved4; scalar_t__* reserved3; scalar_t__* reserved2; scalar_t__* reserved1; struct secs_attr attributes; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SIZE ; 
 int SECS_ATTR_RSV4_SIZE ; 
 int SECS_RSV1_SIZE ; 
 int SECS_RSV2_SIZE ; 
 int SECS_RSV3_SIZE ; 
 int SECS_RSV4_SIZE ; 

__attribute__((used)) static int
sgx_secs_validate(struct sgx_softc *sc, struct secs *secs)
{
	struct secs_attr *attr;
	int i;

	if (secs->size == 0)
		return (EINVAL);

	/* BASEADDR must be naturally aligned on an SECS.SIZE boundary. */
	if (secs->base & (secs->size - 1))
		return (EINVAL);

	/* SECS.SIZE must be at least 2 pages. */
	if (secs->size < 2 * PAGE_SIZE)
		return (EINVAL);

	if ((secs->size & (secs->size - 1)) != 0)
		return (EINVAL);

	attr = &secs->attributes;

	if (attr->reserved1 != 0 ||
	    attr->reserved2 != 0 ||
	    attr->reserved3 != 0)
		return (EINVAL);

	for (i = 0; i < SECS_ATTR_RSV4_SIZE; i++)
		if (attr->reserved4[i])
			return (EINVAL);

	/*
	 * Intel® Software Guard Extensions Programming Reference
	 * 6.7.2 Relevant Fields in Various Data Structures
	 * 6.7.2.1 SECS.ATTRIBUTES.XFRM
	 * XFRM[1:0] must be set to 0x3.
	 */
	if ((attr->xfrm & 0x3) != 0x3)
		return (EINVAL);

	if (!attr->mode64bit)
		return (EINVAL);

	if (secs->size > sc->enclave_size_max)
		return (EINVAL);

	for (i = 0; i < SECS_RSV1_SIZE; i++)
		if (secs->reserved1[i])
			return (EINVAL);

	for (i = 0; i < SECS_RSV2_SIZE; i++)
		if (secs->reserved2[i])
			return (EINVAL);

	for (i = 0; i < SECS_RSV3_SIZE; i++)
		if (secs->reserved3[i])
			return (EINVAL);

	for (i = 0; i < SECS_RSV4_SIZE; i++)
		if (secs->reserved4[i])
			return (EINVAL);

	return (0);
}