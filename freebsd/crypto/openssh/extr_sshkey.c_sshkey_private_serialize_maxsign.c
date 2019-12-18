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
typedef  int /*<<< orphan*/  u_int32_t ;
struct sshkey {int dummy; } ;
struct sshbuf {int dummy; } ;
typedef  int /*<<< orphan*/  sshkey_printfn ;

/* Variables and functions */
 int /*<<< orphan*/  SSHKEY_SERIALIZE_DEFAULT ; 
 int sshkey_private_serialize_opt (struct sshkey const*,struct sshbuf*,int /*<<< orphan*/ ) ; 

int
sshkey_private_serialize_maxsign(const struct sshkey *k, struct sshbuf *b,
    u_int32_t maxsign, sshkey_printfn *pr)
{
	return sshkey_private_serialize_opt(k, b, SSHKEY_SERIALIZE_DEFAULT);
}