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
struct sk_buff {int dummy; } ;
struct crypto_stat_compress {void* stat_err_cnt; void* stat_decompress_tlen; void* stat_decompress_cnt; void* stat_compress_tlen; void* stat_compress_cnt; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  err_cnt; int /*<<< orphan*/  decompress_tlen; int /*<<< orphan*/  decompress_cnt; int /*<<< orphan*/  compress_tlen; int /*<<< orphan*/  compress_cnt; } ;
struct TYPE_4__ {TYPE_1__ compress; } ;
struct crypto_alg {TYPE_2__ stats; } ;
typedef  int /*<<< orphan*/  racomp ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTOCFGA_STAT_ACOMP ; 
 void* atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct crypto_stat_compress*,int /*<<< orphan*/ ,int) ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct crypto_stat_compress*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int crypto_report_acomp(struct sk_buff *skb, struct crypto_alg *alg)
{
	struct crypto_stat_compress racomp;

	memset(&racomp, 0, sizeof(racomp));

	strscpy(racomp.type, "acomp", sizeof(racomp.type));
	racomp.stat_compress_cnt = atomic64_read(&alg->stats.compress.compress_cnt);
	racomp.stat_compress_tlen = atomic64_read(&alg->stats.compress.compress_tlen);
	racomp.stat_decompress_cnt =  atomic64_read(&alg->stats.compress.decompress_cnt);
	racomp.stat_decompress_tlen = atomic64_read(&alg->stats.compress.decompress_tlen);
	racomp.stat_err_cnt = atomic64_read(&alg->stats.compress.err_cnt);

	return nla_put(skb, CRYPTOCFGA_STAT_ACOMP, sizeof(racomp), &racomp);
}