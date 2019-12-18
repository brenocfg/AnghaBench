#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mac_veriexec_file_info {TYPE_1__* ops; int /*<<< orphan*/  fingerprint; } ;
struct TYPE_2__ {int /*<<< orphan*/  digest_len; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fingerprintcmp(struct mac_veriexec_file_info *ip, unsigned char *digest)
{

	return memcmp(ip->fingerprint, digest, ip->ops->digest_len);
}