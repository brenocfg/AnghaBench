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
struct chap {int /*<<< orphan*/  chap_response; int /*<<< orphan*/  chap_challenge; int /*<<< orphan*/  chap_id; } ;
typedef  int /*<<< orphan*/  expected_response ;

/* Variables and functions */
 int CHAP_DIGEST_LEN ; 
 int /*<<< orphan*/  chap_compute_md5 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int,char*,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 

int
chap_authenticate(struct chap *chap, const char *secret)
{
	char expected_response[CHAP_DIGEST_LEN];

	chap_compute_md5(chap->chap_id, secret,
	    chap->chap_challenge, sizeof(chap->chap_challenge),
	    expected_response, sizeof(expected_response));

	if (memcmp(chap->chap_response,
	    expected_response, sizeof(expected_response)) != 0) {
		return (-1);
	}

	return (0);
}