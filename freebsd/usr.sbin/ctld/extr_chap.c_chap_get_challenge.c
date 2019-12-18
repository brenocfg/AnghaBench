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
struct chap {int /*<<< orphan*/  chap_challenge; } ;

/* Variables and functions */
 char* chap_bin2hex (int /*<<< orphan*/ ,int) ; 

char *
chap_get_challenge(const struct chap *chap)
{
	char *chap_c;

	chap_c = chap_bin2hex(chap->chap_challenge,
	    sizeof(chap->chap_challenge));

	return (chap_c);
}