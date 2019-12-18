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
 size_t openpgp_trust_revoke (char*) ; 
 int /*<<< orphan*/ * parse_certificates (unsigned char*,size_t,size_t*) ; 
 size_t ve_forbidden_anchors_add (int /*<<< orphan*/ *,size_t) ; 

size_t
ve_trust_anchors_revoke(unsigned char *buf, size_t len)
{
	br_x509_certificate *xcs;
	size_t num;

	num = 0;
	xcs = parse_certificates(buf, len, &num);
	if (xcs != NULL) {
		num = ve_forbidden_anchors_add(xcs, num);
#ifdef VE_OPENPGP_SUPPORT
	} else {
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		num = openpgp_trust_revoke((char *)buf);
#endif
	}
	return (num);
}