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
struct asymmetric_key_id {size_t len; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct asymmetric_key_id* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct asymmetric_key_id* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,size_t) ; 

struct asymmetric_key_id *asymmetric_key_generate_id(const void *val_1,
						     size_t len_1,
						     const void *val_2,
						     size_t len_2)
{
	struct asymmetric_key_id *kid;

	kid = kmalloc(sizeof(struct asymmetric_key_id) + len_1 + len_2,
		      GFP_KERNEL);
	if (!kid)
		return ERR_PTR(-ENOMEM);
	kid->len = len_1 + len_2;
	memcpy(kid->data, val_1, len_1);
	memcpy(kid->data + len_1, val_2, len_2);
	return kid;
}