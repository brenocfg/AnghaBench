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
struct ipqbucket {int dummy; } ;
struct ipq {int /*<<< orphan*/  ipq_nfrags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSTAT_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipq_free (struct ipqbucket*,struct ipq*) ; 
 int /*<<< orphan*/  ips_fragtimeout ; 

__attribute__((used)) static inline void
ipq_timeout(struct ipqbucket *bucket, struct ipq *fp)
{

	IPSTAT_ADD(ips_fragtimeout, fp->ipq_nfrags);
	ipq_free(bucket, fp);
}