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
struct chap {int /*<<< orphan*/  chap_id; } ;

/* Variables and functions */
 int asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 

char *
chap_get_id(const struct chap *chap)
{
	char *chap_i;
	int ret;

	ret = asprintf(&chap_i, "%d", chap->chap_id);
	if (ret < 0)
		log_err(1, "asprintf");

	return (chap_i);
}