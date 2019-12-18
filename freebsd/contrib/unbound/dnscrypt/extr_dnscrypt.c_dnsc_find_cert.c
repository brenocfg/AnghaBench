#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sldns_buffer {int dummy; } ;
struct dnscrypt_query_header {int /*<<< orphan*/  magic_query; } ;
struct dnsc_env {size_t signed_certs_count; TYPE_1__* certs; } ;
struct TYPE_3__ {int /*<<< orphan*/  magic_query; } ;
typedef  TYPE_1__ dnsccert ;

/* Variables and functions */
 int /*<<< orphan*/  DNSCRYPT_MAGIC_HEADER_LEN ; 
 scalar_t__ DNSCRYPT_QUERY_HEADER_SIZE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_buffer_begin (struct sldns_buffer*) ; 
 scalar_t__ sldns_buffer_limit (struct sldns_buffer*) ; 

__attribute__((used)) static const dnsccert *
dnsc_find_cert(struct dnsc_env* dnscenv, struct sldns_buffer* buffer)
{
	const dnsccert *certs = dnscenv->certs;
	struct dnscrypt_query_header *dnscrypt_header;
	size_t i;

	if (sldns_buffer_limit(buffer) < DNSCRYPT_QUERY_HEADER_SIZE) {
		return NULL;
	}
	dnscrypt_header = (struct dnscrypt_query_header *)sldns_buffer_begin(buffer);
	for (i = 0U; i < dnscenv->signed_certs_count; i++) {
		if (memcmp(certs[i].magic_query, dnscrypt_header->magic_query,
                   DNSCRYPT_MAGIC_HEADER_LEN) == 0) {
			return &certs[i];
		}
	}
	return NULL;
}