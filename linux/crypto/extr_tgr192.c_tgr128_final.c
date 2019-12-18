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
typedef  int /*<<< orphan*/  u8 ;
struct shash_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TGR128_DIGEST_SIZE ; 
 int /*<<< orphan*/  TGR192_DIGEST_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memzero_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tgr192_final (struct shash_desc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tgr128_final(struct shash_desc *desc, u8 * out)
{
	u8 D[64];

	tgr192_final(desc, D);
	memcpy(out, D, TGR128_DIGEST_SIZE);
	memzero_explicit(D, TGR192_DIGEST_SIZE);

	return 0;
}