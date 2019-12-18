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
typedef  int /*<<< orphan*/  isc_sockaddr_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
 int ISC_SOCKADDR_CMPADDR ; 
 int ISC_SOCKADDR_CMPSCOPE ; 
 int /*<<< orphan*/  isc_sockaddr_compare (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

isc_boolean_t
isc_sockaddr_eqaddr(const isc_sockaddr_t *a, const isc_sockaddr_t *b) {
	return (isc_sockaddr_compare(a, b, ISC_SOCKADDR_CMPADDR|
					   ISC_SOCKADDR_CMPSCOPE));
}