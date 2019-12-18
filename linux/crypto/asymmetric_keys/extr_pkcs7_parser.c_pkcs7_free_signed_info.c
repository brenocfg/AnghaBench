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
struct pkcs7_signed_info {int /*<<< orphan*/  sig; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pkcs7_signed_info*) ; 
 int /*<<< orphan*/  public_key_signature_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pkcs7_free_signed_info(struct pkcs7_signed_info *sinfo)
{
	if (sinfo) {
		public_key_signature_free(sinfo->sig);
		kfree(sinfo);
	}
}