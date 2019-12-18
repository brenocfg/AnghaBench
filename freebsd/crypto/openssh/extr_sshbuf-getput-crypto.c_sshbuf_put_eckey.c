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
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_KEY_get0_group (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_KEY_get0_public_key (int /*<<< orphan*/  const*) ; 
 int sshbuf_put_ec (struct sshbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sshbuf_put_eckey(struct sshbuf *buf, const EC_KEY *v)
{
	return sshbuf_put_ec(buf, EC_KEY_get0_public_key(v),
	    EC_KEY_get0_group(v));
}