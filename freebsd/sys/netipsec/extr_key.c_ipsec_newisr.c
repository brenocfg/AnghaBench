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
struct ipsecrequest {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IPSEC_SR ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 struct ipsecrequest* malloc (int,int /*<<< orphan*/ ,int) ; 

struct ipsecrequest *
ipsec_newisr(void)
{

	return (malloc(sizeof(struct ipsecrequest), M_IPSEC_SR,
	    M_NOWAIT | M_ZERO));
}