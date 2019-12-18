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
struct rchap {int /*<<< orphan*/  rchap_secret; } ;

/* Variables and functions */
 struct rchap* calloc (int,int) ; 
 int /*<<< orphan*/  checked_strdup (char const*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 

struct rchap *
rchap_new(const char *secret)
{
	struct rchap *rchap;

	rchap = calloc(1, sizeof(*rchap));
	if (rchap == NULL)
		log_err(1, "calloc");

	rchap->rchap_secret = checked_strdup(secret);

	return (rchap);
}