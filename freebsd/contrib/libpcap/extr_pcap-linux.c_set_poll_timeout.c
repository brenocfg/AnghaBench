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
struct utsname {char* release; } ;
struct pcap_linux {int timeout; scalar_t__ tp_version; int poll_timeout; } ;

/* Variables and functions */
 scalar_t__ TPACKET_V3 ; 
 int strtol (char*,char**,int) ; 
 scalar_t__ uname (struct utsname*) ; 

__attribute__((used)) static void
set_poll_timeout(struct pcap_linux *handlep)
{
#ifdef HAVE_TPACKET3
	struct utsname utsname;
	char *version_component, *endp;
	int major, minor;
	int broken_tpacket_v3 = 1;

	/*
	 * Some versions of TPACKET_V3 have annoying bugs/misfeatures
	 * around which we have to work.  Determine if we have those
	 * problems or not.
	 */
	if (uname(&utsname) == 0) {
		/*
		 * 3.19 is the first release with a fixed version of
		 * TPACKET_V3.  We treat anything before that as
		 * not haveing a fixed version; that may really mean
		 * it has *no* version.
		 */
		version_component = utsname.release;
		major = strtol(version_component, &endp, 10);
		if (endp != version_component && *endp == '.') {
			/*
			 * OK, that was a valid major version.
			 * Get the minor version.
			 */
			version_component = endp + 1;
			minor = strtol(version_component, &endp, 10);
			if (endp != version_component &&
			    (*endp == '.' || *endp == '\0')) {
				/*
				 * OK, that was a valid minor version.
				 * Is this 3.19 or newer?
				 */
				if (major >= 4 || (major == 3 && minor >= 19)) {
					/* Yes. TPACKET_V3 works correctly. */
					broken_tpacket_v3 = 0;
				}
			}
		}
	}
#endif
	if (handlep->timeout == 0) {
#ifdef HAVE_TPACKET3
		/*
		 * XXX - due to a set of (mis)features in the TPACKET_V3
		 * kernel code prior to the 3.19 kernel, blocking forever
		 * with a TPACKET_V3 socket can, if few packets are
		 * arriving and passing the socket filter, cause most
		 * packets to be dropped.  See libpcap issue #335 for the
		 * full painful story.
		 *
		 * The workaround is to have poll() time out very quickly,
		 * so we grab the frames handed to us, and return them to
		 * the kernel, ASAP.
		 */
		if (handlep->tp_version == TPACKET_V3 && broken_tpacket_v3)
			handlep->poll_timeout = 1;	/* don't block for very long */
		else
#endif
			handlep->poll_timeout = -1;	/* block forever */
	} else if (handlep->timeout > 0) {
#ifdef HAVE_TPACKET3
		/*
		 * For TPACKET_V3, the timeout is handled by the kernel,
		 * so block forever; that way, we don't get extra timeouts.
		 * Don't do that if we have a broken TPACKET_V3, though.
		 */
		if (handlep->tp_version == TPACKET_V3 && !broken_tpacket_v3)
			handlep->poll_timeout = -1;	/* block forever, let TPACKET_V3 wake us up */
		else
#endif
			handlep->poll_timeout = handlep->timeout;	/* block for that amount of time */
	} else {
		/*
		 * Non-blocking mode; we call poll() to pick up error
		 * indications, but we don't want it to wait for
		 * anything.
		 */
		handlep->poll_timeout = 0;
	}
}