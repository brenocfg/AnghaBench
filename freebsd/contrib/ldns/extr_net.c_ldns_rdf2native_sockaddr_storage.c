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
typedef  scalar_t__ uint16_t ;
struct sockaddr_storage {int dummy; } ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 scalar_t__ LDNS_PORT ; 
 struct sockaddr_storage* ldns_rdf2native_sockaddr_storage_port (int /*<<< orphan*/  const*,scalar_t__,size_t*) ; 

struct sockaddr_storage *
ldns_rdf2native_sockaddr_storage(
		const ldns_rdf *rd, uint16_t port, size_t *size)
{
	return ldns_rdf2native_sockaddr_storage_port(
			rd, (port == 0 ? (uint16_t)LDNS_PORT : port), size);
}