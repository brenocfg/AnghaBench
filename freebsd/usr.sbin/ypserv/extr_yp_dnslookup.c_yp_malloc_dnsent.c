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
struct circleq_dnsentry {int dummy; } ;

/* Variables and functions */
 struct circleq_dnsentry* malloc (int) ; 
 int /*<<< orphan*/  yp_error (char*) ; 

__attribute__((used)) static struct
circleq_dnsentry *yp_malloc_dnsent(void)
{
	register struct circleq_dnsentry *q;

	q = malloc(sizeof(struct circleq_dnsentry));

	if (q == NULL) {
		yp_error("failed to malloc() circleq dns entry");
		return(NULL);
	}

	return(q);
}