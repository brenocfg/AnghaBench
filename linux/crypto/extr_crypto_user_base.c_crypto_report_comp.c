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
struct sk_buff {int dummy; } ;
struct crypto_report_comp {int /*<<< orphan*/  type; } ;
struct crypto_alg {int dummy; } ;
typedef  int /*<<< orphan*/  rcomp ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTOCFGA_REPORT_COMPRESS ; 
 int /*<<< orphan*/  memset (struct crypto_report_comp*,int /*<<< orphan*/ ,int) ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct crypto_report_comp*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int crypto_report_comp(struct sk_buff *skb, struct crypto_alg *alg)
{
	struct crypto_report_comp rcomp;

	memset(&rcomp, 0, sizeof(rcomp));

	strscpy(rcomp.type, "compression", sizeof(rcomp.type));

	return nla_put(skb, CRYPTOCFGA_REPORT_COMPRESS, sizeof(rcomp), &rcomp);
}