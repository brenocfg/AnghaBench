#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int32_t ;
struct cryptocap {size_t cc_session_size; int cc_flags; int /*<<< orphan*/  cc_dev; scalar_t__ cc_sessions; } ;
typedef  TYPE_1__* crypto_session_t ;
struct TYPE_6__ {void* softc; } ;

/* Variables and functions */
 int CRYPTOCAP_F_CLEANUP ; 
 int /*<<< orphan*/  CRYPTODEV_FREESESSION (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  CRYPTO_DRIVER_LOCK () ; 
 int /*<<< orphan*/  CRYPTO_DRIVER_UNLOCK () ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_CRYPTO_DATA ; 
 struct cryptocap* crypto_drivers ; 
 size_t crypto_drivers_num ; 
 int /*<<< orphan*/  crypto_remove (struct cryptocap*) ; 
 size_t crypto_ses2hid (TYPE_1__*) ; 
 int /*<<< orphan*/  cryptoses_zone ; 
 int /*<<< orphan*/  explicit_bzero (void*,size_t) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
crypto_freesession(crypto_session_t cses)
{
	struct cryptocap *cap;
	void *ses;
	size_t ses_size;
	u_int32_t hid;

	if (cses == NULL)
		return;

	CRYPTO_DRIVER_LOCK();

	hid = crypto_ses2hid(cses);
	KASSERT(hid < crypto_drivers_num,
	    ("bogus crypto_session %p hid %u", cses, hid));
	cap = &crypto_drivers[hid];

	ses = cses->softc;
	ses_size = cap->cc_session_size;

	if (cap->cc_sessions)
		cap->cc_sessions--;

	/* Call the driver cleanup routine, if available. */
	CRYPTODEV_FREESESSION(cap->cc_dev, cses);

	explicit_bzero(ses, ses_size);
	free(ses, M_CRYPTO_DATA);
	uma_zfree(cryptoses_zone, cses);

	if (cap->cc_flags & CRYPTOCAP_F_CLEANUP)
		crypto_remove(cap);

	CRYPTO_DRIVER_UNLOCK();
}