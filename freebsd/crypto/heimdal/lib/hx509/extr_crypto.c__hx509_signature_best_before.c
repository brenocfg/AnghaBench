#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct signature_alg {scalar_t__ best_before; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_3__ {int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_1__ AlgorithmIdentifier ;

/* Variables and functions */
 int HX509_CRYPTO_ALGORITHM_BEST_BEFORE ; 
 int HX509_SIG_ALG_NO_SUPPORTED ; 
 struct signature_alg* find_sig_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 

int
_hx509_signature_best_before(hx509_context context,
			     const AlgorithmIdentifier *alg,
			     time_t t)
{
    const struct signature_alg *md;

    md = find_sig_alg(&alg->algorithm);
    if (md == NULL) {
	hx509_clear_error_string(context);
	return HX509_SIG_ALG_NO_SUPPORTED;
    }
    if (md->best_before && md->best_before < t) {
	hx509_set_error_string(context, 0, HX509_CRYPTO_ALGORITHM_BEST_BEFORE,
			       "Algorithm %s has passed it best before date",
			       md->name);
	return HX509_CRYPTO_ALGORITHM_BEST_BEFORE;
    }
    return 0;
}