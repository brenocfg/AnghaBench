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
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
#define  NID_sha1 128 
 int dasync_digest_nids (int const**) ; 
 int /*<<< orphan*/ * dasync_sha1 () ; 

__attribute__((used)) static int dasync_digests(ENGINE *e, const EVP_MD **digest,
                          const int **nids, int nid)
{
    int ok = 1;
    if (!digest) {
        /* We are returning a list of supported nids */
        return dasync_digest_nids(nids);
    }
    /* We are being asked for a specific digest */
    switch (nid) {
    case NID_sha1:
        *digest = dasync_sha1();
        break;
    default:
        ok = 0;
        *digest = NULL;
        break;
    }
    return ok;
}