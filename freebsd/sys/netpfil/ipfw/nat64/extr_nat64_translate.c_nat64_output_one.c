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
struct nat64_counters {int dummy; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int nat64_output (int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ *,struct nat64_counters*,void*) ; 

__attribute__((used)) static int
nat64_output_one(struct mbuf *m, struct nat64_counters *stats, void *logdata)
{

	return (nat64_output(NULL, m, NULL, stats, logdata));
}