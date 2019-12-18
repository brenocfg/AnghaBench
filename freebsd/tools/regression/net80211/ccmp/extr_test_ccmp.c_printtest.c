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
struct ciphertest {int keyix; int /*<<< orphan*/  plaintext_len; int /*<<< orphan*/  key_len; int /*<<< orphan*/  pn; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
printtest(const struct ciphertest *t)
{
	printf("keyix %u pn %llu key_len %u plaintext_len %u\n"
		, t->keyix
		, t->pn
		, t->key_len
		, t->plaintext_len
	);
}