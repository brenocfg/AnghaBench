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
struct rtattr {int dummy; } ;
struct crypto_template {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (char const*) ; 
 int PTR_ERR (char const*) ; 
 char* crypto_attr_alg_name (struct rtattr*) ; 
 int crypto_gcm_create_common (struct crypto_template*,struct rtattr**,char const*,char const*) ; 

__attribute__((used)) static int crypto_gcm_base_create(struct crypto_template *tmpl,
				  struct rtattr **tb)
{
	const char *ctr_name;
	const char *ghash_name;

	ctr_name = crypto_attr_alg_name(tb[1]);
	if (IS_ERR(ctr_name))
		return PTR_ERR(ctr_name);

	ghash_name = crypto_attr_alg_name(tb[2]);
	if (IS_ERR(ghash_name))
		return PTR_ERR(ghash_name);

	return crypto_gcm_create_common(tmpl, tb, ctr_name, ghash_name);
}