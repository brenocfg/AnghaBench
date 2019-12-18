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
struct crypt_op {int ses; size_t len; void* mac; void const* src; } ;
typedef  int /*<<< orphan*/  cop ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_CHECK_MSG (int,char*) ; 
 int /*<<< orphan*/  CIOCCRYPT ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct crypt_op*) ; 
 int /*<<< orphan*/  memset (struct crypt_op*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
do_cryptop(int fd, int ses, const void *inp, size_t inlen, void *out)
{
	struct crypt_op cop;

	memset(&cop, 0, sizeof(cop));

	cop.ses = ses;
	cop.len = inlen;
	cop.src = inp;
	cop.mac = out;
	ATF_CHECK_MSG(ioctl(fd, CIOCCRYPT, &cop) >= 0, "ioctl(CIOCCRYPT)");
}