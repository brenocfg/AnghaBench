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
struct simd_aead_alg {int dummy; } ;
struct TYPE_2__ {char* cra_name; char* cra_driver_name; } ;
struct aead_alg {TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct simd_aead_alg*) ; 
 int PTR_ERR (struct simd_aead_alg*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int crypto_register_aeads (struct aead_alg*,int) ; 
 struct simd_aead_alg* simd_aead_create_compat (char const*,char const*,char const*) ; 
 int /*<<< orphan*/  simd_unregister_aeads (struct aead_alg*,int,struct simd_aead_alg**) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

int simd_register_aeads_compat(struct aead_alg *algs, int count,
			       struct simd_aead_alg **simd_algs)
{
	int err;
	int i;
	const char *algname;
	const char *drvname;
	const char *basename;
	struct simd_aead_alg *simd;

	err = crypto_register_aeads(algs, count);
	if (err)
		return err;

	for (i = 0; i < count; i++) {
		WARN_ON(strncmp(algs[i].base.cra_name, "__", 2));
		WARN_ON(strncmp(algs[i].base.cra_driver_name, "__", 2));
		algname = algs[i].base.cra_name + 2;
		drvname = algs[i].base.cra_driver_name + 2;
		basename = algs[i].base.cra_driver_name;
		simd = simd_aead_create_compat(algname, drvname, basename);
		err = PTR_ERR(simd);
		if (IS_ERR(simd))
			goto err_unregister;
		simd_algs[i] = simd;
	}
	return 0;

err_unregister:
	simd_unregister_aeads(algs, count, simd_algs);
	return err;
}