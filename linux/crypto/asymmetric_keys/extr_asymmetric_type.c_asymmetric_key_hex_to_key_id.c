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
struct asymmetric_key_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct asymmetric_key_id* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __asymmetric_key_hex_to_key_id (char const*,struct asymmetric_key_id*,size_t) ; 
 int /*<<< orphan*/  kfree (struct asymmetric_key_id*) ; 
 struct asymmetric_key_id* kmalloc (int,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 

struct asymmetric_key_id *asymmetric_key_hex_to_key_id(const char *id)
{
	struct asymmetric_key_id *match_id;
	size_t asciihexlen;
	int ret;

	if (!*id)
		return ERR_PTR(-EINVAL);
	asciihexlen = strlen(id);
	if (asciihexlen & 1)
		return ERR_PTR(-EINVAL);

	match_id = kmalloc(sizeof(struct asymmetric_key_id) + asciihexlen / 2,
			   GFP_KERNEL);
	if (!match_id)
		return ERR_PTR(-ENOMEM);
	ret = __asymmetric_key_hex_to_key_id(id, match_id, asciihexlen / 2);
	if (ret < 0) {
		kfree(match_id);
		return ERR_PTR(-EINVAL);
	}
	return match_id;
}