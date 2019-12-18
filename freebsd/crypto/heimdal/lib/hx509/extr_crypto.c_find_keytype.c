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
struct signature_alg {int /*<<< orphan*/  const* key_oid; } ;
typedef  TYPE_1__* hx509_private_key ;
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_3__ {int /*<<< orphan*/  signature_alg; } ;

/* Variables and functions */
 struct signature_alg* find_sig_alg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const heim_oid *
find_keytype(const hx509_private_key key)
{
    const struct signature_alg *md;

    if (key == NULL)
	return NULL;

    md = find_sig_alg(key->signature_alg);
    if (md == NULL)
	return NULL;
    return md->key_oid;
}