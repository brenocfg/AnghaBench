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
struct sshbuf {int dummy; } ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_INT_NE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_hex2bn (int /*<<< orphan*/ **,char const*) ; 
 struct sshbuf* load_text_file (char const*) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 scalar_t__ sshbuf_ptr (struct sshbuf*) ; 

BIGNUM *
load_bignum(const char *name)
{
	BIGNUM *ret = NULL;
	struct sshbuf *buf;

	buf = load_text_file(name);
	ASSERT_INT_NE(BN_hex2bn(&ret, (const char *)sshbuf_ptr(buf)), 0);
	sshbuf_free(buf);
	return ret;
}