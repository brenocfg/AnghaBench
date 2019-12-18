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
struct rchap {int dummy; } ;

/* Variables and functions */
 int chap_hex2bin (char const*,void**,size_t*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  log_debugx (char*,char const*) ; 
 int /*<<< orphan*/  rchap_receive_bin (struct rchap*,unsigned char,void*,size_t) ; 
 unsigned char strtoul (char const*,int /*<<< orphan*/ *,int) ; 

int
rchap_receive(struct rchap *rchap, const char *id, const char *challenge)
{
	unsigned char id_bin;
	void *challenge_bin;
	size_t challenge_bin_len;

	int error;

	id_bin = strtoul(id, NULL, 10);

	error = chap_hex2bin(challenge, &challenge_bin, &challenge_bin_len);
	if (error != 0) {
		log_debugx("got incorrectly encoded CHAP challenge \"%s\"",
		    challenge);
		return (1);
	}

	rchap_receive_bin(rchap, id_bin, challenge_bin, challenge_bin_len);
	free(challenge_bin);

	return (0);
}