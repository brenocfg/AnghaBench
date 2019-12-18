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
struct sctp_ifa {int localifa_flags; scalar_t__ src_is_priv; scalar_t__ src_is_loop; scalar_t__ src_is_glob; TYPE_1__ address; } ;
typedef  scalar_t__ sa_family_t ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SCTPDBG_ADDR (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int SCTP_ADDR_IFA_UNUSEABLE ; 
 int /*<<< orphan*/  SCTP_DEBUG_OUTPUT2 ; 
 int /*<<< orphan*/  SCTP_DEBUG_OUTPUT3 ; 

__attribute__((used)) static struct sctp_ifa *
sctp_is_ifa_addr_preferred(struct sctp_ifa *ifa,
    uint8_t dest_is_loop,
    uint8_t dest_is_priv,
    sa_family_t fam)
{
	uint8_t dest_is_global = 0;

	/* dest_is_priv is true if destination is a private address */
	/* dest_is_loop is true if destination is a loopback addresses */

	/**
	 * Here we determine if its a preferred address. A preferred address
	 * means it is the same scope or higher scope then the destination.
	 * L = loopback, P = private, G = global
	 * -----------------------------------------
	 *    src    |  dest | result
	 *  ----------------------------------------
	 *     L     |    L  |    yes
	 *  -----------------------------------------
	 *     P     |    L  |    yes-v4 no-v6
	 *  -----------------------------------------
	 *     G     |    L  |    yes-v4 no-v6
	 *  -----------------------------------------
	 *     L     |    P  |    no
	 *  -----------------------------------------
	 *     P     |    P  |    yes
	 *  -----------------------------------------
	 *     G     |    P  |    no
	 *   -----------------------------------------
	 *     L     |    G  |    no
	 *   -----------------------------------------
	 *     P     |    G  |    no
	 *    -----------------------------------------
	 *     G     |    G  |    yes
	 *    -----------------------------------------
	 */

	if (ifa->address.sa.sa_family != fam) {
		/* forget mis-matched family */
		return (NULL);
	}
	if ((dest_is_priv == 0) && (dest_is_loop == 0)) {
		dest_is_global = 1;
	}
	SCTPDBG(SCTP_DEBUG_OUTPUT2, "Is destination preferred:");
	SCTPDBG_ADDR(SCTP_DEBUG_OUTPUT2, &ifa->address.sa);
	/* Ok the address may be ok */
#ifdef INET6
	if (fam == AF_INET6) {
		/* ok to use deprecated addresses? no lets not! */
		if (ifa->localifa_flags & SCTP_ADDR_IFA_UNUSEABLE) {
			SCTPDBG(SCTP_DEBUG_OUTPUT3, "NO:1\n");
			return (NULL);
		}
		if (ifa->src_is_priv && !ifa->src_is_loop) {
			if (dest_is_loop) {
				SCTPDBG(SCTP_DEBUG_OUTPUT3, "NO:2\n");
				return (NULL);
			}
		}
		if (ifa->src_is_glob) {
			if (dest_is_loop) {
				SCTPDBG(SCTP_DEBUG_OUTPUT3, "NO:3\n");
				return (NULL);
			}
		}
	}
#endif
	/*
	 * Now that we know what is what, implement or table this could in
	 * theory be done slicker (it used to be), but this is
	 * straightforward and easier to validate :-)
	 */
	SCTPDBG(SCTP_DEBUG_OUTPUT3, "src_loop:%d src_priv:%d src_glob:%d\n",
	    ifa->src_is_loop, ifa->src_is_priv, ifa->src_is_glob);
	SCTPDBG(SCTP_DEBUG_OUTPUT3, "dest_loop:%d dest_priv:%d dest_glob:%d\n",
	    dest_is_loop, dest_is_priv, dest_is_global);

	if ((ifa->src_is_loop) && (dest_is_priv)) {
		SCTPDBG(SCTP_DEBUG_OUTPUT3, "NO:4\n");
		return (NULL);
	}
	if ((ifa->src_is_glob) && (dest_is_priv)) {
		SCTPDBG(SCTP_DEBUG_OUTPUT3, "NO:5\n");
		return (NULL);
	}
	if ((ifa->src_is_loop) && (dest_is_global)) {
		SCTPDBG(SCTP_DEBUG_OUTPUT3, "NO:6\n");
		return (NULL);
	}
	if ((ifa->src_is_priv) && (dest_is_global)) {
		SCTPDBG(SCTP_DEBUG_OUTPUT3, "NO:7\n");
		return (NULL);
	}
	SCTPDBG(SCTP_DEBUG_OUTPUT3, "YES\n");
	/* its a preferred address */
	return (ifa);
}