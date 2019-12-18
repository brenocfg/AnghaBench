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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  br_x509_trust_anchor ;
typedef  int /*<<< orphan*/  br_x509_certificate ;
typedef  int /*<<< orphan*/  anchor_list ;

/* Variables and functions */
 int /*<<< orphan*/  VEC_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ anchor_verbose ; 
 scalar_t__ certificate_to_trust_anchor_inner (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,char const*) ; 
 char* x509_cn_get (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static size_t
ve_anchors_add(br_x509_certificate *xcs, size_t num, anchor_list *anchors,
    const char *anchors_name)
{
	br_x509_trust_anchor ta;
	size_t u;

	for (u = 0; u < num; u++) {
		if (certificate_to_trust_anchor_inner(&ta, &xcs[u]) < 0) {
			break;
		}
		VEC_ADD(*anchors, ta);
		if (anchor_verbose && anchors_name) {
			char buf[64];
			char *cp;

			cp = x509_cn_get(&xcs[u], buf, sizeof(buf));
			if (cp) {
				printf("x509_anchor(%s) %s\n", cp, anchors_name);
			}
		}
	}
	return (u);
}