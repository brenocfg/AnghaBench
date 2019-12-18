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
struct key_restriction {int /*<<< orphan*/ * keytype; struct key* key; int /*<<< orphan*/  check; } ;
struct key {int dummy; } ;
typedef  int /*<<< orphan*/  key_restrict_link_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct key_restriction* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  key_type_asymmetric ; 
 struct key_restriction* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct key_restriction *asymmetric_restriction_alloc(
	key_restrict_link_func_t check,
	struct key *key)
{
	struct key_restriction *keyres =
		kzalloc(sizeof(struct key_restriction), GFP_KERNEL);

	if (!keyres)
		return ERR_PTR(-ENOMEM);

	keyres->check = check;
	keyres->key = key;
	keyres->keytype = &key_type_asymmetric;

	return keyres;
}