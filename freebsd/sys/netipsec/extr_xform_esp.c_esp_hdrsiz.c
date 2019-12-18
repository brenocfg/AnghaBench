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
struct secasvar {int flags; scalar_t__ replay; int /*<<< orphan*/ * tdb_authalgxform; TYPE_1__* tdb_encalgxform; } ;
struct newesp {int dummy; } ;
struct esp {int dummy; } ;
struct TYPE_2__ {scalar_t__ blocksize; } ;

/* Variables and functions */
 int EALG_MAX_BLOCK_LEN ; 
 int /*<<< orphan*/  IPSEC_ASSERT (int /*<<< orphan*/ ,char*) ; 
 int SADB_X_EXT_OLD ; 
 scalar_t__ ah_hdrsiz (struct secasvar*) ; 

size_t
esp_hdrsiz(struct secasvar *sav)
{
	size_t size;

	if (sav != NULL) {
		/*XXX not right for null algorithm--does it matter??*/
		IPSEC_ASSERT(sav->tdb_encalgxform != NULL,
			("SA with null xform"));
		if (sav->flags & SADB_X_EXT_OLD)
			size = sizeof (struct esp);
		else
			size = sizeof (struct newesp);
		size += sav->tdb_encalgxform->blocksize + 9;
		/*XXX need alg check???*/
		if (sav->tdb_authalgxform != NULL && sav->replay)
			size += ah_hdrsiz(sav);
	} else {
		/*
		 *   base header size
		 * + max iv length for CBC mode
		 * + max pad length
		 * + sizeof (pad length field)
		 * + sizeof (next header field)
		 * + max icv supported.
		 */
		size = sizeof (struct newesp) + EALG_MAX_BLOCK_LEN + 9 + 16;
	}
	return size;
}