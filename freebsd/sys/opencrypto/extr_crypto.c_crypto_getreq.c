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
struct cryptop {struct cryptodesc* crp_desc; } ;
struct cryptodesc {struct cryptodesc* crd_next; } ;

/* Variables and functions */
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  crypto_freereq (struct cryptop*) ; 
 int /*<<< orphan*/  cryptodesc_zone ; 
 int /*<<< orphan*/  cryptop_zone ; 
 void* uma_zalloc (int /*<<< orphan*/ ,int) ; 

struct cryptop *
crypto_getreq(int num)
{
	struct cryptodesc *crd;
	struct cryptop *crp;

	crp = uma_zalloc(cryptop_zone, M_NOWAIT|M_ZERO);
	if (crp != NULL) {
		while (num--) {
			crd = uma_zalloc(cryptodesc_zone, M_NOWAIT|M_ZERO);
			if (crd == NULL) {
				crypto_freereq(crp);
				return NULL;
			}

			crd->crd_next = crp->crp_desc;
			crp->crp_desc = crd;
		}
	}
	return crp;
}