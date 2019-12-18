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
typedef  int /*<<< orphan*/  br_x509_certificate ;

/* Variables and functions */
 scalar_t__ load_key_file (char const*) ; 
 int /*<<< orphan*/ * read_certificates (char const*,size_t*) ; 
 size_t ve_trust_anchors_add (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static size_t
trust_file_add(const char *trust)
{
	br_x509_certificate *xcs;
	size_t num;

	xcs = read_certificates(trust, &num);
	if (xcs) {
		num = ve_trust_anchors_add(xcs, num);
	}
#ifdef VE_OPENPGP_SUPPORT
	else if (load_key_file(trust)) {
		num = 1;
	}
#endif
	return (num);
}