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
struct key_preparsed_payload {int /*<<< orphan*/  datalen; int /*<<< orphan*/  data; } ;
typedef  enum key_being_used_for { ____Placeholder_key_being_used_for } key_being_used_for ;

/* Variables and functions */
 int EINVAL ; 
 int NR__KEY_BEING_USED_FOR ; 
 int /*<<< orphan*/  VERIFY_USE_SECONDARY_KEYRING ; 
 int pkcs7_usage ; 
 int /*<<< orphan*/  pkcs7_view_content ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int verify_pkcs7_signature (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct key_preparsed_payload*) ; 

__attribute__((used)) static int pkcs7_preparse(struct key_preparsed_payload *prep)
{
	enum key_being_used_for usage = pkcs7_usage;

	if (usage >= NR__KEY_BEING_USED_FOR) {
		pr_err("Invalid usage type %d\n", usage);
		return -EINVAL;
	}

	return verify_pkcs7_signature(NULL, 0,
				      prep->data, prep->datalen,
				      VERIFY_USE_SECONDARY_KEYRING, usage,
				      pkcs7_view_content, prep);
}