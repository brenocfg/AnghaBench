#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {scalar_t__ sa_family; } ;
struct TYPE_3__ {TYPE_2__ sa; } ;
struct sctp_ifa {int localifa_flags; int src_is_loop; scalar_t__ src_is_priv; TYPE_1__ address; } ;
typedef  scalar_t__ sa_family_t ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SCTPDBG_ADDR (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int SCTP_ADDR_IFA_UNUSEABLE ; 
 int /*<<< orphan*/  SCTP_DEBUG_OUTPUT3 ; 

__attribute__((used)) static struct sctp_ifa *
sctp_is_ifa_addr_acceptable(struct sctp_ifa *ifa,
    uint8_t dest_is_loop,
    uint8_t dest_is_priv,
    sa_family_t fam)
{
	uint8_t dest_is_global = 0;

	/**
	 * Here we determine if its a acceptable address. A acceptable
	 * address means it is the same scope or higher scope but we can
	 * allow for NAT which means its ok to have a global dest and a
	 * private src.
	 *
	 * L = loopback, P = private, G = global
	 * -----------------------------------------
	 *  src    |  dest | result
	 * -----------------------------------------
	 *   L     |   L   |    yes
	 *  -----------------------------------------
	 *   P     |   L   |    yes-v4 no-v6
	 *  -----------------------------------------
	 *   G     |   L   |    yes
	 * -----------------------------------------
	 *   L     |   P   |    no
	 * -----------------------------------------
	 *   P     |   P   |    yes
	 * -----------------------------------------
	 *   G     |   P   |    yes - May not work
	 * -----------------------------------------
	 *   L     |   G   |    no
	 * -----------------------------------------
	 *   P     |   G   |    yes - May not work
	 * -----------------------------------------
	 *   G     |   G   |    yes
	 * -----------------------------------------
	 */

	if (ifa->address.sa.sa_family != fam) {
		/* forget non matching family */
		SCTPDBG(SCTP_DEBUG_OUTPUT3, "ifa_fam:%d fam:%d\n",
		    ifa->address.sa.sa_family, fam);
		return (NULL);
	}
	/* Ok the address may be ok */
	SCTPDBG_ADDR(SCTP_DEBUG_OUTPUT3, &ifa->address.sa);
	SCTPDBG(SCTP_DEBUG_OUTPUT3, "dst_is_loop:%d dest_is_priv:%d\n",
	    dest_is_loop, dest_is_priv);
	if ((dest_is_loop == 0) && (dest_is_priv == 0)) {
		dest_is_global = 1;
	}
#ifdef INET6
	if (fam == AF_INET6) {
		/* ok to use deprecated addresses? */
		if (ifa->localifa_flags & SCTP_ADDR_IFA_UNUSEABLE) {
			return (NULL);
		}
		if (ifa->src_is_priv) {
			/* Special case, linklocal to loop */
			if (dest_is_loop)
				return (NULL);
		}
	}
#endif
	/*
	 * Now that we know what is what, implement our table. This could in
	 * theory be done slicker (it used to be), but this is
	 * straightforward and easier to validate :-)
	 */
	SCTPDBG(SCTP_DEBUG_OUTPUT3, "ifa->src_is_loop:%d dest_is_priv:%d\n",
	    ifa->src_is_loop,
	    dest_is_priv);
	if ((ifa->src_is_loop == 1) && (dest_is_priv)) {
		return (NULL);
	}
	SCTPDBG(SCTP_DEBUG_OUTPUT3, "ifa->src_is_loop:%d dest_is_glob:%d\n",
	    ifa->src_is_loop,
	    dest_is_global);
	if ((ifa->src_is_loop == 1) && (dest_is_global)) {
		return (NULL);
	}
	SCTPDBG(SCTP_DEBUG_OUTPUT3, "address is acceptable\n");
	/* its an acceptable address */
	return (ifa);
}