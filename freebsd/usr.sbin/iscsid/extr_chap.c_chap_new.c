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
struct chap {int /*<<< orphan*/  chap_id; int /*<<< orphan*/ * chap_challenge; } ;

/* Variables and functions */
 int /*<<< orphan*/  arc4random_buf (int /*<<< orphan*/ *,int) ; 
 struct chap* calloc (int,int) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 

struct chap *
chap_new(void)
{
	struct chap *chap;

	chap = calloc(1, sizeof(*chap));
	if (chap == NULL)
		log_err(1, "calloc");

	/*
	 * Generate the challenge.
	 */
	arc4random_buf(chap->chap_challenge, sizeof(chap->chap_challenge));
	arc4random_buf(&chap->chap_id, sizeof(chap->chap_id));

	return (chap);
}