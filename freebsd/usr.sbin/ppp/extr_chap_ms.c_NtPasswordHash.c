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
typedef  int /*<<< orphan*/  MD4_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD4Final (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD4Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD4Update (int /*<<< orphan*/ *,char*,int) ; 

void
NtPasswordHash(char *key, int keylen, char *hash)
{
  MD4_CTX MD4context;

  MD4Init(&MD4context);
  MD4Update(&MD4context, key, keylen);
  MD4Final(hash, &MD4context);
}