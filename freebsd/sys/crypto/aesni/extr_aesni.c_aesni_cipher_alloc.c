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
struct cryptop {int /*<<< orphan*/  crp_buf; int /*<<< orphan*/  crp_flags; } ;
struct cryptodesc {int /*<<< orphan*/  crd_len; int /*<<< orphan*/  crd_skip; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_AESNI ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/ * crypto_contiguous_subsegment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_copydata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t *
aesni_cipher_alloc(struct cryptodesc *enccrd, struct cryptop *crp,
    bool *allocated)
{
	uint8_t *addr;

	addr = crypto_contiguous_subsegment(crp->crp_flags,
	    crp->crp_buf, enccrd->crd_skip, enccrd->crd_len);
	if (addr != NULL) {
		*allocated = false;
		return (addr);
	}
	addr = malloc(enccrd->crd_len, M_AESNI, M_NOWAIT);
	if (addr != NULL) {
		*allocated = true;
		crypto_copydata(crp->crp_flags, crp->crp_buf, enccrd->crd_skip,
		    enccrd->crd_len, addr);
	} else
		*allocated = false;
	return (addr);
}