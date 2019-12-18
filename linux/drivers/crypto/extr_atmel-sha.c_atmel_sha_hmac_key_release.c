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
struct atmel_sha_hmac_key {int /*<<< orphan*/  keydup; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct atmel_sha_hmac_key*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void atmel_sha_hmac_key_release(struct atmel_sha_hmac_key *hkey)
{
	kfree(hkey->keydup);
	memset(hkey, 0, sizeof(*hkey));
}